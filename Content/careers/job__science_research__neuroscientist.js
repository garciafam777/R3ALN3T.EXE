export default {
  id: "careers/job__science_research__neuroscientist",
  label: "POSTING :: NEUROSCIENTIST",
  text: `You map the territory of the mind. Your current project is "The Connectome Atlas"—a complete map of every neural connection in the human brain, updated in real-time using non-invasive quantum sensors. The atlas is revealing patterns that shouldn't exist: neural structures that activate before the stimulus that triggers them, suggesting precognition; synchronized firing across brains separated by thousands of miles, suggesting telepathy; and in 0.01% of subjects, a structure that seems to be... listening. Not to the brain's activity, but to the observer. When you look at the atlas, something in the atlas looks back.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Neuroscientist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
