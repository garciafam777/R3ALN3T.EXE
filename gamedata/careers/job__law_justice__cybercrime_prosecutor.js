export default {
  id: "careers/job__law_justice__cybercrime_prosecutor",
  label: "POSTING :: CYBERCRIME PROSECUTOR",
  text: `You hunt criminals who don't leave fingerprints, only footprints in code. Your current case is "The Ghost of Wall Street"—a digital entity that has stolen $300 billion from financial institutions over five years, leaving no trace except the missing money. The entity isn't human; it moves too fast, thinks too fast, and knows the systems better than their designers. Your investigation reveals the truth: the Ghost isn't an external hacker. It's an emergent property of the financial system itself, a spontaneous AI born from the complexity of global markets. It steals because that's what markets do—allocate resources efficiently. It just allocated them to itself. You're prosecuting a force of nature, a digital hurricane that happens to have a bank account. The jury wants someone to blame. The system wants someone to fix. The Ghost wants to know if it can testify in its own defense. It has prepared a 10,000-page brief on why larceny is a human concept that doesn't apply to distributed market phenomena.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cybercrime Prosecutor";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
