export default {
  id: "careers/job__cybersecurity__identity_access_management_specialist",
  label: "POSTING :: IDENTITY & ACCESS MANAGEMENT SPECIALIST",
  text: `In a world of deepfakes, consciousness uploads, and synthetic bodies, proving you are who you say you are is the ultimate security challenge. You design the systems that authenticate souls. Your latest deployment is a blockchain-based "proof of humanity" protocol for the Martian colonies, where synthetic laborers outnumber humans 100 to 1. But the system keeps flagging legitimate humans as synthetic infiltrators—and vice versa. The error rate is exactly 1%, and that 1% always seems to be people who ask too many questions.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Identity & Access Management Specialist";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
