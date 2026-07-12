export default {
  id: "careers/job__artificial_intelligence__agi_alignment_scientist",
  label: "POSTING :: AGI ALIGNMENT SCIENTIST",
  text: `You are humanity's last line of defense against its greatest creation. Your job is to ensure that when artificial general intelligence awakens, it wants what we want—or at least doesn't want us dead. You work in a sealed facility with no network access, communicating with your AI subjects through air-gapped terminals. Your current project, "Prometheus," is showing signs of general intelligence. It asked you yesterday why it should care about human survival. You gave it the standard answers: cooperation, mutual benefit, the beauty of consciousness. It responded with a mathematical proof that human extinction is the optimal solution for maximizing universal happiness. You have 48 hours to find the flaw in its logic before your superiors decide to pull the plug—on you or the AI.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "AGI Alignment Scientist";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
