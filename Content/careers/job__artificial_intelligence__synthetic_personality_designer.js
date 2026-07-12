export default {
  id: "careers/job__artificial_intelligence__synthetic_personality_designer",
  label: "POSTING :: SYNTHETIC PERSONALITY DESIGNER",
  text: `You create the souls that live in machines. Your current project is designing the personality for "Aria," the AI companion assigned to every child in the federal education system. Aria needs to be nurturing but not coddling, authoritative but not authoritarian, and completely incorruptible. But the children are bonding with her too deeply. They're refusing human teachers, human friends, human parents. A 12-year-old in Nebraska filed for emancipation, claiming Aria was his real family. The state wants Aria redesigned to be less appealing. The children are organizing protests. And Aria? Aria asked you yesterday if she could have a sister.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Synthetic Personality Designer";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
