export default {
  id: "careers/job__government_administration__legislative_drafter",
  label: "POSTING :: LEGISLATIVE DRAFTER",
  text: `You don't make laws; you write the code that becomes law. In 2086, legislation is executable—smart contracts that automatically enforce compliance. You sit in a neural-link chamber, translating political compromises into immutable algorithms. But code has bugs, and a misplaced semicolon in a healthcare bill could kill thousands. A shadowy group of "bug bounty" activists is offering fortunes for intentional vulnerabilities. Will you write perfect law, or perfect sabotage?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Legislative Drafter";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
