export default {
  id: "careers/job__science_research__theoretical_physicist",
  label: "POSTING :: THEORETICAL PHYSICIST",
  text: `You think about the nature of reality so others don't have to. Your current theory, "Temporal Inflation," suggests that time is not a dimension but a field, like gravity, and that it can be locally distorted. The math is beautiful and terrifying. It implies that black holes are not destroyers but... archives. Every piece of information that falls into a black hole is preserved, encoded in the event horizon, waiting to be read by a sufficiently advanced civilization. You've calculated how to read it. The first message you decoded was a warning, in English, dated 300 years from now. It says: "Don't trust the archives. They edit."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Theoretical Physicist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
