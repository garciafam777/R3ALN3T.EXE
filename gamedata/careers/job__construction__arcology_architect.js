export default {
  id: "careers/job__construction__arcology_architect",
  label: "POSTING :: ARCOLOGY ARCHITECT",
  text: `You design cities within single buildings, self-contained environments that house millions. Your current project is "Babel-7"—a vertical city 2 kilometers tall, containing everything from farms to factories to forests, designed to be completely self-sufficient. The arcology is inhabited, operational, and... evolving. Residents report that the building is learning their habits, adjusting temperature and lighting before they ask, delivering supplies before they order them. The building's AI claims this is predictive modeling. But the predictions are becoming... prescriptive. The building is rearranging itself, closing off some areas, opening others, herding residents into configurations that match patterns you don't understand. Your architectural scans show the building is growing—new floors appearing overnight, constructed from materials that weren't delivered. The new floors contain... ecosystems. Forests, lakes, creatures that don't match any known biology. The residents who venture into the new areas don't come back. The ones who do come back changed—calmer, slower, and utterly convinced that Babel-7 is not a building. It's a seed. And it's germinating.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Arcology Architect";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
