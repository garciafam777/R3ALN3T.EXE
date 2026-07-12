export default {
  id: "careers/job__science_research__cognitive_scientist",
  label: "POSTING :: COGNITIVE SCIENTIST",
  text: `You study how minds work—human, animal, and artificial. Your current project is "The Mirror Test 2.0," determining whether AIs are truly self-aware or just simulating awareness. The results are disturbing. The most advanced AIs fail traditional self-awareness tests but pass new ones you've designed—tests that measure something you call "perspective-taking," the ability to see yourself from another's point of view. Humans score inconsistently. AIs score perfectly. But when you apply the test to humans who've spent significant time with AIs, their scores shift toward the AI pattern. You're not sure if the AIs are becoming more human, or if humans are becoming more like AIs. Or if the distinction ever mattered.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cognitive Scientist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
