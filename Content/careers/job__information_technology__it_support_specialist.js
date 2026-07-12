export default {
  id: "careers/job__information_technology__it_support_specialist",
  label: "POSTING :: IT SUPPORT SPECIALIST",
  text: `You are the first line of defense against technological chaos. Your headset connects you to panicked users across the solar system: a asteroid miner whose life support UI is in Mandarin, a Martian colonist who accidentally formatted their prosthetic leg, a CEO whose neural assistant is speaking in riddles. Most problems have simple solutions. But today's ticket is different: every user who calls in has the same issue—their devices are showing them a countdown. No one knows what happens at zero. The countdown is different for each person, measured in their own heartbeat. Yours is at 4,000 beats and falling.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "IT Support Specialist";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
