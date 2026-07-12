export default {
  id: "careers/job__cybersecurity__red_team_operator",
  label: "POSTING :: RED TEAM OPERATOR",
  text: `You are the wolf in the fold. Hired by corporations and governments to break their own systems, you spend your nights in darkened rooms, fingers dancing across holographic keyboards, probing firewalls that think faster than you do. Your latest contract: penetrate the quantum-encrypted vault of the world's largest cryptocurrency exchange. The catch? If you succeed, you learn where $2 trillion in untraceable assets are stored. If you fail, your consciousness gets uploaded to a penalty box—a digital prison where a thousand years pass in a single afternoon.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Red Team Operator";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
