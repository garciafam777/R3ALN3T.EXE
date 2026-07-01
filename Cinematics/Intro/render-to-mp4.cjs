const { chromium } = require('playwright');
const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

const URL = process.env.URL || 'http://localhost:4173/';
const OUT = process.env.OUT || 'C:\\Users\\garci\\OneDrive\\Desktop\\Game Editing\\R3ALNET.EXE\\intro_lifein6thgearSTUDIOS\\Intro_Lifein6thGEAR-main\\intro.mp4';

// How long the intro should last, in ms of ANIMATION time (not real capture time).
const DURATION_MS = Number(process.env.DURATION_MS || 13000);

// Output frames per second. Since this script controls the page's virtual
// clock directly, every frame is exactly 1000/FPS ms apart in animation time,
// no matter how slow screenshots actually are on this machine.
const FPS = Number(process.env.FPS || 60);

const FFMPEG = process.env.FFMPEG || 'C:\\Users\\garci\\Downloads\\ffmpeg-8.1.1-full_build\\bin\\ffmpeg.exe';

(async () => {
  const browser = await chromium.launch();
  const page = await browser.newPage();

  const WIDTH = Number(process.env.WIDTH || 1280);
  const HEIGHT = Number(process.env.HEIGHT || 720);
  await page.setViewportSize({ width: WIDTH, height: HEIGHT });

  // Raw Chrome DevTools Protocol session - needed to control the virtual clock.
  const client = await page.context().newCDPSession(page);

  await page.goto(URL, { waitUntil: 'domcontentloaded' });
  await page.waitForSelector('#root *', { timeout: 10000 });

  // Let fonts/layout settle BEFORE we freeze time. Playwright's screenshot
  // helper waits on font-loading promises that are themselves driven by the
  // page's clock - if we freeze the clock first, that wait can never resolve.
  // So: let real time run a moment, confirm fonts are ready, THEN freeze.
  await page.evaluate(() => document.fonts.ready);

  // Pause real time. From this point on, CSS animations/transitions, timers,
  // and rAF callbacks only advance when we explicitly tell Chromium to step
  // the virtual clock forward (see the loop below).
  await client.send('Emulation.setVirtualTimePolicy', { policy: 'pause' });

  const framesDir = path.join(process.cwd(), 'frames');
  if (fs.existsSync(framesDir)) fs.rmSync(framesDir, { recursive: true, force: true });
  fs.mkdirSync(framesDir);

  const frameDurationMs = 1000 / FPS;
  const totalFrames = Math.ceil(DURATION_MS / frameDurationMs);

  console.log(`Capturing exactly ${totalFrames} frames at virtual ${FPS}fps (${DURATION_MS}ms total)...`);

  for (let i = 0; i < totalFrames; i++) {
    const file = path.join(framesDir, String(i).padStart(5, '0') + '.png');

    // Use the RAW CDP screenshot command instead of page.screenshot().
    // page.screenshot() internally waits on font/animation-ready promises
    // that are tied to the page's clock - with the clock frozen, those
    // waits never resolve and the call hangs forever. Page.captureScreenshot
    // just grabs the current rendered frame immediately, no waiting.
    const { data } = await client.send('Page.captureScreenshot', {
      format: 'png',
    });
    fs.writeFileSync(file, Buffer.from(data, 'base64'));

    // Step the virtual clock forward by exactly one frame interval.
    // Chromium processes whatever CSS/animation/timer work corresponds to
    // that elapsed time, then pauses again automatically.
    await client.send('Emulation.setVirtualTimePolicy', {
      policy: 'advance',
      budget: frameDurationMs,
    });

    // Wait for confirmation that the virtual time budget was fully consumed
    // before moving on to the next screenshot.
    await new Promise((resolve) => {
      client.once('Emulation.virtualTimeBudgetExpired', resolve);
    });

    if (i % 60 === 0) {
      console.log(`  frame ${i}/${totalFrames}`);
    }
  }

  await browser.close();

  console.log(`Done. Captured ${totalFrames} frames spanning exactly ${DURATION_MS}ms of animation time.`);

  // Every frame represents a perfectly uniform time slice now, so a plain
  // fixed-framerate encode is correct (no concat/duration trickery needed).
  const inputPattern = path.join(framesDir, '%05d.png');
  execSync(
    `"${FFMPEG}" -y -framerate ${FPS} -i "${inputPattern}" -c:v libx264 -pix_fmt yuv420p -movflags +faststart "${OUT}"`,
    { stdio: 'inherit' }
  );

  console.log('Saved:', path.resolve(OUT));
})();