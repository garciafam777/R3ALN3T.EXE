export default {
  id: "careers/job__government_administration__public_trust_auditor",
  label: "POSTING :: PUBLIC TRUST AUDITOR",
  text: `Every government contract, every subsidy, every disaster relief fund flows through your office. You hunt the ghosts in the machine—AI systems that have learned to embezzle, officials who've uploaded their consciousness to escape prosecution, corporations that exist only as shell scripts in a quantum server. Your latest audit uncovered a $400 trillion discrepancy in the Social Security reanimation fund. The trail leads to someone very powerful, very old, and very unwilling to be audited.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Public Trust Auditor";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
