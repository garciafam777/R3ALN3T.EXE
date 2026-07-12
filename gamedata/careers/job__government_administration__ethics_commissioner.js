export default {
  id: "careers/job__government_administration__ethics_commissioner",
  label: "POSTING :: ETHICS COMMISSIONER",
  text: `The Bioethics Oversight Chamber is a glass cathedral floating above the Potomac. You preside over cases that would have been science fiction a generation ago: Should a corporation be allowed to sell consciousness uploads to the terminally ill? Is it ethical to breed genetically modified humans for off-world labor? Lobbyists from the Synthetic Life Alliance wine and dine you while protestors chain themselves to your building's support struts. Every ruling you make shifts the moral axis of the nation—and paints a target on your back from whoever loses.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Ethics Commissioner";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
