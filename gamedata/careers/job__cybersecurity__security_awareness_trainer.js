export default {
  id: "careers/job__cybersecurity__security_awareness_trainer",
  label: "POSTING :: SECURITY AWARENESS TRAINER",
  text: `You teach humans not to be the weakest link. In an era of neural phishing and emotional manipulation algorithms, your job is to inoculate people against social engineering. You design simulations so realistic that trainees sometimes can't tell when the exercise ends and reality begins. Your latest program has a 40% failure rate—unprecedentedly high. The failures all share one trait: they grew up in the same state, attended the same school, and received the same childhood vaccine. Coincidence, or the longest-con social engineering attack in history?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Security Awareness Trainer";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
