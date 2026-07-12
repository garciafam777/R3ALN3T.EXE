export default {
  id: "careers/job__cybersecurity__secure_software_developer",
  label: "POSTING :: SECURE SOFTWARE DEVELOPER",
  text: `You write code that cannot be hacked—mathematically proven secure, formally verified, unbreakable. The trade-off is that it runs slowly and costs fortunes to develop. Your current client is building a voting system for the first post-human election, where AI citizens will outnumber biological voters. The opposition party wants you to insert a "statistical anomaly" that gives them a 3% edge. They know where your daughter goes to school—on Mars, in a dome you can't afford to visit.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Secure Software Developer";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
