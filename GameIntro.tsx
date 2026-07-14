import { useEffect, useState } from 'react';

interface GameIntroProps {
  onIntroComplete?: () => void;
}

export default function GameIntro({ onIntroComplete }: GameIntroProps) {
  const [phase, setPhase] = useState(0);
  const [skipPressed, setSkipPressed] = useState(false);

  useEffect(() => {
    if (skipPressed) {
      onIntroComplete?.();
      return;
    }

    const timers = [
      // Phase 1: System boot-up text (0-2s)
      setTimeout(() => setPhase(1), 300),
      // Phase 2: "NEURAL NETWORK INITIALIZING" (1-2.5s)
      setTimeout(() => setPhase(2), 1000),
      // Phase 3: Loading bar (2.5-4s)
      setTimeout(() => setPhase(3), 2500),
      // Phase 4: "NETP CONSTRUCT INTERFACE ONLINE" (4-5s)
      setTimeout(() => setPhase(4), 4000),
      // Phase 5: Main story text (5-7s)
      setTimeout(() => setPhase(5), 5000),
      // Phase 6: Fade transition (7-8s)
      setTimeout(() => setPhase(6), 7000),
      // Phase 7: Game start
      setTimeout(() => {
        setPhase(7);
        onIntroComplete?.();
      }, 8000),
    ];

    return () => timers.forEach(clearTimeout);
  }, [skipPressed, onIntroComplete]);

  const handleSkip = () => {
    setSkipPressed(true);
  };

  return (
    <div className="min-h-screen bg-[#0a0a0a] text-white flex flex-col items-center justify-center relative overflow-hidden">
      {/* Glitch/Noise background */}
      <div className="absolute inset-0 bg-[radial-gradient(ellipse_at_center,rgba(50,50,80,0.1)_0%,rgba(10,10,10,1)_70%)]" />
      
      {/* Scanlines overlay */}
      <div className="absolute inset-0 pointer-events-none">
        <div className="absolute inset-0 opacity-5 bg-repeat" style={{
          backgroundImage: 'repeating-linear-gradient(0deg, #000 0px, #000 1px, transparent 1px, transparent 2px)'
        }} />
      </div>

      {/* Main Content */}
      <div className="relative z-10 flex flex-col items-center justify-center w-full h-screen px-4">
        
        {/* PHASE 1-2: System Boot Text */}
        <div className={`text-center mb-8 transition-all duration-500 ${
          phase >= 1 && phase < 5 ? 'opacity-100' : 'opacity-0'
        }`}>
          <div className="font-mono text-sm md:text-base text-[#00ff00] mb-2 text-shadow-glow">
            > SYSTEM BOOT SEQUENCE
          </div>
          <div className="font-mono text-xs md:text-sm text-[#00aa00] mb-4">
            {phase >= 2 ? (
              <span className="animate-typewriter">
                NEURAL NETWORK INITIALIZING...
                {phase >= 2 && phase < 3 && <span className="animate-pulse">_</span>}
              </span>
            ) : null}
          </div>

          {/* Loading Bar */}
          {phase >= 3 && (
            <div className="w-48 h-1 bg-[#1a1a2e] border border-[#00ff00] rounded overflow-hidden">
              <div className={`h-full bg-gradient-to-r from-[#00ff00] to-[#00aa00] transition-all duration-1000 ${
                phase >= 4 ? 'w-full' : 'w-0'
              }`} />
            </div>
          )}

          {/* NETP Online Message */}
          {phase >= 4 && (
            <div className="mt-4 font-mono text-xs md:text-sm text-[#00ff00] animate-pulse">
              ✓ NETP CONSTRUCT INTERFACE ONLINE
            </div>
          )}
        </div>

        {/* PHASE 5: Main Story Text */}
        {phase >= 5 && phase < 6 && (
          <div className="max-w-2xl text-center animate-fadeIn">
            <h1 className="font-display text-3xl md:text-5xl font-bold text-white mb-6 text-shadow-3d">
              R3ALN3T.EXE
            </h1>
            
            <div className="space-y-4 text-sm md:text-base text-white/90 leading-relaxed font-light">
              <p className="animate-slideIn">
                The digital frontier has collapsed. Corporate overlords battle for network supremacy, 
                wielding NetP Constructs—sentient AI entities born from code, chaos, and control.
              </p>
              
              <p className="animate-slideIn" style={{ animationDelay: '0.2s' }}>
                You are a newly awakened NetP entity—neither fully digital nor entirely artificial. 
                Your past is fragmented. Your purpose unclear.
              </p>
              
              <p className="animate-slideIn text-[#00ff00]" style={{ animationDelay: '0.4s' }}>
                But one thing is certain: <span className="font-bold">The network demands players.</span>
              </p>
            </div>

            <div className="mt-8 pt-4 border-t border-[#00ff00]/30">
              <p className="text-xs md:text-sm text-[#00aa00] font-mono">
                [ CONSTRUCT PROFILE LOADING... ]
              </p>
            </div>
          </div>
        )}

        {/* PHASE 6-7: Fade to Game */}
        {phase >= 6 && (
          <div className="fixed inset-0 bg-black animate-fadeIn pointer-events-none z-50" />
        )}
      </div>

      {/* Skip Button */}
      {phase < 6 && (
        <button
          onClick={handleSkip}
          className="absolute bottom-4 right-4 z-20 px-4 py-2 border border-[#00ff00]/50 text-[#00ff00] hover:border-[#00ff00] hover:text-white font-mono text-xs transition-all duration-300 hover:bg-[#00ff00]/10"
        >
          [ SKIP &gt; ]
        </button>
      )}

      {/* Glitch effect pseudo-element */}
      {phase >= 4 && phase < 6 && (
        <div className="absolute inset-0 pointer-events-none z-30">
          <div className="absolute inset-0 bg-gradient-to-b from-transparent via-[#00ff00]/5 to-transparent animate-pulse" />
        </div>
      )}
    </div>
  );
}
