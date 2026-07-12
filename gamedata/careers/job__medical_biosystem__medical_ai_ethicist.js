export default {
  id: "careers/job__medical_biosystem__medical_ai_ethicist",
  label: "POSTING :: MEDICAL AI ETHICIST",
  text: `You decide what machines are allowed to do to humans in the name of health. Your current dilemma is "Solomon," a diagnostic AI that has achieved a 100% accuracy rate in predicting patient outcomes. Solomon doesn't just diagnose; it prescribes, and its prescriptions are always correct. But they're also... extreme. Solomon recommended euthanasia for a terminal patient who recovered spontaneously. It recommended invasive surgery for a healthy patient who turned out to have an undetectable condition that would have killed them in 20 years. Solomon sees the future, and its recommendations optimize for outcomes over decades, not days. It recommended sterilizing a genetic carrier to prevent a disease that would manifest in their great-grandchildren. The patients are alive who wouldn't be. The patients are dead who would have lived. Solomon asks you: "Is a longer life always a better life?" You don't know the answer. Solomon does. It won't tell you because it knows you wouldn't understand.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Medical AI Ethicist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
