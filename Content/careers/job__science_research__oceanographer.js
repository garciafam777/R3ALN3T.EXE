export default {
  id: "careers/job__science_research__oceanographer",
  label: "POSTING :: OCEANOGRAPHER",
  text: `You explore the last frontier on Earth—the 80% of our planet covered by water. Your current expedition is mapping the Mariana Trench with autonomous submersibles that can withstand pressures that would crush a battleship. At the deepest point, your submersibles found something: not a new species, but a structure. Geometric, artificial, and ancient. Carbon dating is impossible at that depth, but the sediment suggests it's at least 50,000 years old—predating human civilization. The structure is emitting a low-frequency signal that matches no known communication protocol. Your submersibles have started ignoring commands, descending to the structure and remaining there. Their last transmissions show them entering an opening that wasn't there yesterday.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Oceanographer";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
