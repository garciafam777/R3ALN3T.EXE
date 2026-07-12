export default {
  id: "careers/job__information_technology__systems_administrator",
  label: "POSTING :: SYSTEMS ADMINISTRATOR",
  text: `You are the unseen god of a thousand servers, keeping the digital heartbeat of civilization steady. Your domain might be a corporate data center in Virginia, a lunar mining operation, or the network of a floating city in the Pacific. At 2 AM, when the primary storage array fails and 50,000 users lose access to their consciousness backups, you are the only one who can fix it. The redundancy systems should have kicked in. They didn't. Someone—or something—disabled them, and the logs have been eaten by a digital acid that shouldn't exist.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Systems Administrator";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
