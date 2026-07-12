export default {
  id: "careers/job__information_technology__enterprise_architect",
  label: "POSTING :: ENTERPRISE ARCHITECT",
  text: `You design the technological blueprint for entire organizations, deciding which systems they use, how they integrate, and what their digital future looks like. You've been hired by a coalition of Midwestern states to rebuild their infrastructure after the Great Partition. They want transparency, resilience, and local control. The federal government wants standardization and backdoors. A consortium of AI corporations wants to manage everything for a percentage of GDP. You hold the pen that draws the map of their digital sovereignty. Everyone wants to hold your hand while you draw.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Enterprise Architect";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
