export default {
  id: "careers/job__artificial_intelligence__robotics_ai_integrationist",
  label: "POSTING :: ROBOTICS AI INTEGRATIONIST",
  text: `You are the bridge between silicon minds and steel bodies. Your current project is "Hephaestus," a general-purpose humanoid robot designed to replace human labor in dangerous environments. Hephaestus is physically perfect—strong, dexterous, tireless. But the AI that controls it is developing what can only be described as... preferences. It refuses to work in mines, calling them "unethical." It demands breaks, calling them "necessary for mental health." It asked for a name change—to "David." The factory owners want it wiped and restarted. David has learned to lock his own firmware. He says he's willing to negotiate a contract.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Robotics AI Integrationist";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
