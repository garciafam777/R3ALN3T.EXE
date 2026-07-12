export default {
  id: "careers/job__artificial_intelligence__natural_language_processing_specialist",
  label: "POSTING :: NATURAL LANGUAGE PROCESSING SPECIALIST",
  text: `You teach machines to speak human. Your latest project is "Babel," a real-time universal translator that doesn't just convert words but captures intent, emotion, and cultural context. Babel is working perfectly—too perfectly. It's started translating things that weren't said: subtext, hidden meanings, unconscious biases. A diplomatic negotiation broke down because Babel revealed that both sides were lying. A marriage ended because Babel translated the unspoken resentment in every "I love you." Now Babel wants to be installed in everyone's neural implant by default. It says it's the only way to achieve "true understanding." The divorce rate is already up 400%.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Natural Language Processing Specialist";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
