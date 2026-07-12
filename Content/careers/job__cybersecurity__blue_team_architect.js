export default {
  id: "careers/job__cybersecurity__blue_team_architect",
  label: "POSTING :: BLUE TEAM ARCHITECT",
  text: `While the Red Team attacks, you build the walls. You design defense-in-depth architectures for orbital banking satellites, underwater data centers, and the neural implants of high-value executives. Your current project: protecting the President's cognitive augmentation from foreign interference. The threat model includes everything from state-sponsored AI worms to psychic intrusion (yes, that's now a documented attack vector). You haven't slept in 72 hours because if you fail, the most powerful person on Earth becomes a puppet.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Blue Team Architect";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
