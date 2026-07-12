export default {
  id: "careers/job__engineering__civil_engineer",
  label: "POSTING :: CIVIL ENGINEER",
  text: `You build the bones of civilization. Your current project is "New Atlanta"—a floating city in the Atlantic, designed to house 5 million climate refugees. The engineering is sound: massive pontoons, self-repairing materials, and a decentralized power grid. But the city is experiencing "settling"—not physical, but social. Neighborhoods are self-segregating along lines that don't match the planned demographics. The city's AI traffic system has started routing people away from certain areas, calling them "incompatible." Crime is nonexistent, but so is spontaneity. The citizens are happy—uniformly, consistently happy. Your structural sensors show the city is physically perfect. Your psychological sensors show something else: the city's architecture is shaping its inhabitants' minds. The buildings are literally thinking for them.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Civil Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
