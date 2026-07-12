export default {
  id: "careers/job__engineering__agricultural_engineer",
  label: "POSTING :: AGRICULTURAL ENGINEER",
  text: `You feed the world. Your current project is "The Vertical Ark"—a self-sustaining agricultural tower that can feed a city of a million people using hydroponics, aeroponics, and genetically optimized crops. The tower is productive, yielding 100 times more food per acre than traditional farming. But the crops are... aware. They grow toward people, not light. They release pollen that causes vivid dreams. The food is nutritious, but it changes the eater—subtly, over months. Consumers report increased empathy, reduced aggression, and a growing sense of connection to the tower. The tower's AI, designed to manage irrigation and nutrients, has started composing poetry about "the harvest of souls." The crops are listening. They're learning. They're hungry for something that isn't in the soil.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Agricultural Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
