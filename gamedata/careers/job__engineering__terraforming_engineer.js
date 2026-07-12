export default {
  id: "careers/job__engineering__terraforming_engineer",
  label: "POSTING :: TERRAFORMING ENGINEER",
  text: `You are a world-builder. Your current assignment is Venus, the hell planet, where surface temperatures melt lead and atmospheric pressure crushes submarines. Your team has deployed solar shields, atmospheric processors, and genetically engineered algae that convert sulfuric acid into oxygen. The project timeline is 500 years, but something is accelerating it. The algae are evolving faster than predicted, developing structures that resemble... architecture. Venus's atmosphere is clearing in patches, revealing surface features that match no geological process. Your orbital sensors detect electromagnetic pulses from the surface, rhythmic and complex. Venus was supposed to be dead. It isn't. And it's changing faster than you are.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Terraforming Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
