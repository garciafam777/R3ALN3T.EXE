export default {
  id: "careers/job__cybersecurity__incident_response_commander",
  label: "POSTING :: INCIDENT RESPONSE COMMANDER",
  text: `When the alarms blare at 3 AM, you are the one who answers. A ransomware attack has locked down a hospital's life-support systems. A supply-chain poison has turned 10,000 autonomous vehicles into kamikaze weapons. A deepfake has convinced the stock market that the President is dead. You lead a team of analysts, forensic bots, and field operatives to contain, eradicate, and recover. The current incident is different—it's your own neural implant that's been compromised, and you're not sure if the commands you're giving are your own.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Incident Response Commander";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
