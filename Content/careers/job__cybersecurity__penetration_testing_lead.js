export default {
  id: "careers/job__cybersecurity__penetration_testing_lead",
  label: "POSTING :: PENETRATION TESTING LEAD",
  text: `You manage a team of ethical hackers who test the defenses of everything from smart cities to orbital weapons platforms. Your team is the best in the business—so good that a foreign intelligence agency has been trying to recruit them. One by one, your operatives are receiving offers they can't refuse: unlimited resources, erased criminal records, resurrected loved ones. Your job is to keep them loyal, but the agency knows your price too. What is it?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Penetration Testing Lead";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
