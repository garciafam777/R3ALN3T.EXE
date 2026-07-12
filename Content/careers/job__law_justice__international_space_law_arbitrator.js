export default {
  id: "careers/job__law_justice__international_space_law_arbitrator",
  label: "POSTING :: INTERNATIONAL SPACE LAW ARBITRATOR",
  text: `You settle disputes where no nation has sovereignty and no treaty has precedent. Your current case: two mining corporations, one American and one Chinese, both claim the same asteroid. The asteroid contains enough rare earth elements to crash the global market for a decade. Both corporations have armed stations in orbit. Both have invoked "the right of first possession." Both are threatening kinetic strikes. Your arbitration must prevent a war that could start in space and end on Earth. The law is unclear, the stakes are existential, and both sides are watching to see if you'll favor your own nationality. You were born in California. The Chinese corporation knows this. The American corporation knows you studied in Beijing. Everyone knows everything. The only question is: what do you know about yourself that they don't?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "International Space Law Arbitrator";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
