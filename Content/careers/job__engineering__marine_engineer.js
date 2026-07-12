export default {
  id: "careers/job__engineering__marine_engineer",
  label: "POSTING :: MARINE ENGINEER",
  text: `You build for the 71% of Earth that isn't land. Your current project is "Aqua-3," a self-sustaining underwater city on the continental shelf, designed to house 100,000 people. The city is a marvel of pressure-resistant architecture, closed-loop life support, and bioluminescent lighting. But the residents are changing. They're developing a preference for low light, high humidity, and silence. They're spending more time in the city's observation domes, staring into the dark water. Some have started sleepwalking into the airlocks. The city's dolphins—genetically enhanced for communication—have stopped talking to humans. They talk to each other more, in patterns that match the city's power fluctuations. The ocean is getting louder. The residents are listening.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Marine Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
