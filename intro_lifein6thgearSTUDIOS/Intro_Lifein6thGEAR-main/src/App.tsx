import { useEffect, useState } from 'react';

export default function App() {
  const [phase, setPhase] = useState(0);

  useEffect(() => {
    const timers = [
      setTimeout(() => setPhase(1), 500),    // "Lifein" appears
      setTimeout(() => setPhase(2), 1500),   // Stamp appears
      setTimeout(() => setPhase(3), 2100),  // "GEA" types
      setTimeout(() => setPhase(4), 2500),  // "R" types
      setTimeout(() => setPhase(5), 3200),  // Studios glows
      setTimeout(() => setPhase(6), 7200),  // Glow fades
    ];

    return () => timers.forEach(clearTimeout);
  }, []);

  return (
    <div className="min-h-screen bg-[#0a0a0a] text-white flex flex-col items-center justify-center relative overflow-hidden px-4">
      {/* Subtle Background Gradient */}
      <div className="absolute inset-0 bg-[radial-gradient(ellipse_at_center,rgba(30,30,30,0.8)_0%,rgba(10,10,10,1)_70%)]" />

      {/* Main Content */}
      <div className="relative z-10 flex flex-col items-center w-full max-w-[95vw]">
        {/* Main Title Row - Responsive flex */}
        <div className="flex items-center justify-center flex-wrap gap-1 sm:gap-2 md:gap-3">
          {/* Lifein */}
          <span
            className={`font-display text-[clamp(2rem,8vw,8rem)] sm:text-[clamp(3rem,10vw,9rem)] md:text-[clamp(4rem,12vw,10rem)] font-bold tracking-tight text-white text-shadow-3d transition-all duration-700 ${
              phase >= 1 ? 'opacity-100 translate-x-0' : 'opacity-0 -translate-x-10'
            }`}
          >
            Lifein
          </span>

          {/* 6TH Stamp */}
          <div
            className={`relative ${
              phase >= 2 ? 'animate-stamp' : 'opacity-0'
            }`}
          >
            <div className="stamp-box">
              <span className="font-display text-[clamp(1.5rem,7vw,7rem)] sm:text-[clamp(2rem,9vw,8rem)] md:text-[clamp(2.5rem,11vw,9rem)] font-black text-[#e53935] tracking-tight text-shadow-red">
                6TH
              </span>
            </div>
          </div>

          {/* GEAR - Typing Effect */}
          <span className="font-mono text-[clamp(2rem,8vw,8rem)] sm:text-[clamp(3rem,10vw,9rem)] md:text-[clamp(4rem,12vw,10rem)] font-bold text-white tracking-wider text-shadow-3d">
            <span className={phase >= 3 ? 'opacity-100' : 'opacity-0'}>GEA</span>
            <span className={phase >= 4 ? 'opacity-100' : 'opacity-0'}>R</span>
            {phase >= 4 && phase < 5 && (
              <span className="inline-block w-2 sm:w-3 h-[0.8em] bg-white ml-1 animate-pulse" />
            )}
          </span>
        </div>

        {/* Studios - Bottom */}
        <div
          className={`mt-4 sm:mt-6 text-center transition-all duration-1000 ${
            phase >= 5 ? 'opacity-100 translate-y-0' : 'opacity-0 translate-y-4'
          }`}
        >
          <span
            className={`font-display text-[clamp(1rem,3vw,2rem)] sm:text-[clamp(1.25rem,4vw,3rem)] md:text-[clamp(1.5rem,5vw,4rem)] font-light tracking-[0.3em] sm:tracking-[0.4em] uppercase text-white/90 ${
              phase >= 5 && phase < 6 ? 'animate-glow' : ''
            } ${phase >= 6 ? 'animate-glow-fade' : ''}`}
          >
            studios
          </span>
        </div>
      </div>

      {/* Fade to Black Overlay at Bottom */}
      <div className="absolute bottom-0 left-0 right-0 h-32 bg-gradient-to-t from-[#0a0a0a] to-transparent pointer-events-none" />

      {/* Subtle Vignette */}
      <div className="absolute inset-0 bg-[radial-gradient(ellipse_at_center,transparent_0%,rgba(0,0,0,0.3)_100%)] pointer-events-none" />
    </div>
  );
}
