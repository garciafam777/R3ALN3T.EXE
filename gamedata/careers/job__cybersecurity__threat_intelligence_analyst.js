export default {
  id: "careers/job__cybersecurity__threat_intelligence_analyst",
  label: "POSTING :: THREAT INTELLIGENCE ANALYST",
  text: `You are a professional paranoid. You monitor dark web forums, intercepted communications, and AI-generated threat models to predict the next cyber catastrophe before it happens. Your current assessment suggests a coordinated attack on the global food distribution AI in 72 hours. The evidence is circumstantial, the sources unreliable, and your superiors want actionable intelligence, not hunches. If you cry wolf and you're wrong, your career ends. If you're right and no one listens, millions starve.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Threat Intelligence Analyst";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
