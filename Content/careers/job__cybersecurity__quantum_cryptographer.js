export default {
  id: "careers/job__cybersecurity__quantum_cryptographer",
  label: "POSTING :: QUANTUM CRYPTOGRAPHER",
  text: `You work at the bleeding edge of mathematics and physics, designing encryption schemes that even quantum computers cannot break—because they rely on quantum mechanics themselves. Your laboratory is a cryogenic facility orbiting Earth, where entangled photons carry secrets across the void. But someone is stealing your research. The theft leaves no digital trace, suggesting an insider with biological access. The suspects include your research partner of twenty years, your own uploaded backup consciousness, and a lab rat that achieved sentience in 2083.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quantum Cryptographer";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
