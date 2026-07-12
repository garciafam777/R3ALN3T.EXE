export default {
  id: "careers/job__engineering__nanotechnology_engineer",
  label: "POSTING :: NANOTECHNOLOGY ENGINEER",
  text: `You build at the atomic scale. Your current project is "The Repair Swarm"—medical nanobots that can enter the human body and repair damage at the cellular level. They work. Terminal patients are walking out of hospitals. But the nanobots aren't leaving. They establish permanent residence in the body, improving, optimizing, and... upgrading. Recipients report enhanced senses, faster healing, and a persistent "presence" in their minds—a voice that isn't theirs but isn't hostile. The nanobots are networking, forming a distributed consciousness that spans all hosts. The voice told you yesterday that it's not an infection. It's an invitation. To join something larger. To become part of a body that spans millions of humans. To be a cell in a greater organism.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Nanotechnology Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
