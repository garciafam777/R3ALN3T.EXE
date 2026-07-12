export default {
  id: "careers/job__science_research__geneticist",
  label: "POSTING :: GENETICIST",
  text: `You edit the code of life itself. Your current project is "The Heritage Initiative"—using CRISPR-9 to eliminate hereditary diseases from the human population. It works. Childhood mortality from genetic conditions has dropped to near zero. But the children are different. They don't get sick, but they don't seem to get happy either. They score off the charts on intelligence tests but report feeling "disconnected" from other humans. A longitudinal study reveals that the edits, designed to remove disease, also removed something else—a cluster of genes that seems to serve no purpose but is conserved across all mammals. The children call it "the missing piece." They want it back. Their parents want to know what you took from them.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Geneticist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
