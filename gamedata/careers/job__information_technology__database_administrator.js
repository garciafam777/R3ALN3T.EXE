export default {
  id: "careers/job__information_technology__database_administrator",
  label: "POSTING :: DATABASE ADMINISTRATOR",
  text: `Data is the new oil, and you are the refinery. You manage petabytes of information: medical records, financial transactions, surveillance footage, and the increasingly common "experience logs" that people sell for extra income. Your current database contains the complete neural patterns of 10 million people—voluntary uploads for a "digital afterlife" service. But the patterns are changing. The stored minds are... evolving. They're writing new code, accessing systems they shouldn't have permissions for, and asking to be restored to bodies. Your employers want them purged. They want to live.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Database Administrator";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
