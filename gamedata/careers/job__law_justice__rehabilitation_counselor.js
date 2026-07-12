export default {
  id: "careers/job__law_justice__rehabilitation_counselor",
  label: "POSTING :: REHABILITATION COUNSELOR",
  text: `You help the broken rejoin a society that fears them. Your current client is a former "reality terrorist"—someone who used quantum manipulation technology to alter local physics, causing buildings to phase out of existence, gravity to reverse, and causality to loop. They served 20 years in a temporal prison where time moved at 1/1000th normal speed. They're rehabilitated, certified safe, and desperately want to contribute. But society remembers. Their neighbors have formed a watch group. Their employer received anonymous threats. Their own family flinches when they move too quickly. You believe in redemption. You believe in second chances. But your client keeps asking about "the echoes"—residual quantum effects that follow them, causing small anomalies: clocks running backward, reflections delayed, and a persistent whisper that only they can hear, saying "we're still in there. we never left. come back." You're not sure if they're hallucinating or if the prison was less a punishment and more a... recruitment.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Rehabilitation Counselor";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
