const { chromium } = require('playwright');
const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

const URL = process.env.URL || 'http://localhost:4173/';
const OUT = process.env.OUT || 'C:\\Users\\garci\\OneDrive\\Desktop\\Game Editing\\R3ALNET.EXE\\intro_lifein6thgearSTUDIOS\\Intro_Lifein6thGEAR-main\\intro.mp4';

// How long the intro should last, in ms of ANIMATION time.
const DURATION_MS = Number(process.env.DURATION_MS || 50000);

// Output frames per second. Every frame is exactly 1000/FPS ms apart in
// animation time because we manually scrub each animation's currentTime -
// real screenshot speed has zero effect on output smoothness or pacing.
const FPS = Number(process.env.FPS || 60);

const FFMPEG = process.env.FFMPEG || 'C:\\Users\\garci\\Downloads\\ffmpeg-8.1.1-full_build\\bin\\ffmpeg.exe';

(async () => {
  const browser = await chromium.launch();
  const page = await browser.newPage();

  const WIDTH = Number(process.env.WIDTH || 1280);
  const HEIGHT = Number(process.env.HEIGHT || 720);
  await page.setViewportSize({ width: WIDTH, height: HEIGHT });

  await page.goto(URL, { waitUntil: 'domcontentloaded' });
  await page.waitForSelector('#root *', { timeout: 10000 });
  await page.evaluate(() => document.fonts.ready);

  // Pause every running CSS animation/transition immediately, then rewind
  // each one to time 0. From here on, nothing moves unless we explicitly
  // set currentTime ourselves before each screenshot.
  const animCount = await page.evaluate(() => {
    const anims = document.getAnimations({ subtree: true });
    for (const a of anims) {
      a.pause();
      a.currentTime = 0;
    }
    return anims.length;
  });

  console.log(`Found and paused ${animCount} animation(s).`);

  if (animCount === 0) {
    console.warn(
      'WARNING: No animations found via document.getAnimations(). ' +
      'This usually means the animation has not started yet at this point ' +
      'in the page lifecycle, or it is not a CSS animation/transition. ' +
      'If frames look static, see the troubleshooting note below.'
    );
  }

  const framesDir = path.join(process.cwd(), 'frames');
  if (fs.existsSync(framesDir)) fs.rmSync(framesDir, { recursive: true, force: true });
  fs.mkdirSync(framesDir);

  const frameDurationMs = 100 / FPS;
  const totalFrames = Math.ceil(DURATION_MS / frameDurationMs);

  console.log(`Capturing exactly ${totalFrames} frames at virtual ${FPS}fps (${DURATION_MS}ms total)...`);

  for (let i = 0; i < totalFrames; i++) {
    const targetTimeMs = i * frameDurationMs;

    // Scrub every animation to this exact moment in time. This is
    // synchronous - the browser recomputes styles immediately, no waiting.
    await page.evaluate((t) => {
      const anims = document.getAnimations({ subtree: true });
      for (const a of anims) {
        a.currentTime = t;
      }
    }, targetTimeMs);

    const file = path.join(framesDir, String(i).padStart(5, '0') + '.png');
    await page.screenshot({ path: file });

    if (i % 60 === 0) {
      console.log(`  frame ${i}/${totalFrames} (t=${targetTimeMs.toFixed(0)}ms)`);
    }
  }

  await browser.close();

  console.log(`Done. Captured ${totalFrames} frames spanning exactly ${DURATION_MS}ms of animation time.`);

  // Every frame represents a perfectly uniform, deterministic time slice,
  // so a plain fixed-framerate encode is correct.
  const inputPattern = path.join(framesDir, '%05d.png');
  execSync(
    `"${FFMPEG}" -y -framerate ${FPS} -i "${inputPattern}" -c:v libx264 -pix_fmt yuv420p -movflags +faststart "${OUT}"`,
    { stdio: 'inherit' }
  );

  console.log('Saved:', path.resolve(OUT));
})();
