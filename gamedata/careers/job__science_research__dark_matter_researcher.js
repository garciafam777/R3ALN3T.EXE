export default {
  id: "careers/job__science_research__dark_matter_researcher",
  label: "POSTING :: DARK MATTER RESEARCHER",
  text: `You hunt the invisible. Deep beneath the South Dakota bedrock, in a chamber shielded from all known particles, you wait for the ghostly touch of dark matter. The universe is 85% invisible, and you are determined to see it. Your detectors have registered something—events that don't match any known interaction. The pattern suggests intelligence: signals at prime-number intervals, responses to your test pulses. The scientific community is divided between those who think you've discovered dark matter life and those who think your equipment is haunted. Your funding depends on a positive result. Your conscience depends on being honest. The signals are getting stronger, and they're asking questions back.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Dark Matter Researcher";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
