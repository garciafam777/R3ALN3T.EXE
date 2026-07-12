export default {
  id: "careers/job__science_research__particle_physicist",
  label: "POSTING :: PARTICLE PHYSICIST",
  text: `You smash atoms together to see what the universe is made of. Your current experiment at the Lunar Supercollider is pushing energies that haven't existed since the Big Bang. The data shows something impossible: particles that travel backward in time, carrying information from the future. The effect is small—a few photons out of trillions—but consistent. Your calculations suggest that at sufficient energies, you could receive a message from the future. Your graduate student points out that you already have: the experiment's safety protocols, designed last year, contain a note in your handwriting that you don't remember writing. It says: "Stop. They are listening."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Particle Physicist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
