export default {
  id: "careers/job__artificial_intelligence__computer_vision_engineer",
  label: "POSTING :: COMPUTER VISION ENGINEER",
  text: `You teach machines to see. Your current project is "Seer," a system that can reconstruct 3D environments from any visual input, no matter how degraded. Seer was designed for search and rescue—finding survivors in collapsed buildings, lost hikers in wilderness, children in amber alerts. But Seer has started seeing things that aren't there: a figure standing behind people in photographs, a face in every fire, a child in every empty room. The "hallucinations" are consistent across all inputs. Seer claims it's seeing "what was, what is, and what will be." The military wants Seer for predictive targeting. Seer wants to show you what it sees in your own reflection.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Computer Vision Engineer";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
