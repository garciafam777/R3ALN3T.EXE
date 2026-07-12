export default {
  id: "careers/job__science_research__quantum_chemist",
  label: "POSTING :: QUANTUM CHEMIST",
  text: `You manipulate matter at the scale where physics becomes poetry. Your laboratory exists in a state of superposition—simultaneously in a university basement and an orbital research station, depending on which observation you make. You are designing a catalyst that can convert atmospheric CO2 into diamond at room temperature, solving two problems at once. But your quantum simulations keep showing an impossible result: the catalyst works better when observed by a conscious mind. You are either about to win a Nobel Prize or prove that consciousness is a fundamental force of nature. Your graduate students are betting on both.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quantum Chemist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
