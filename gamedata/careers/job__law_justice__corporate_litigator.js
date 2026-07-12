export default {
  id: "careers/job__law_justice__corporate_litigator",
  label: "POSTING :: CORPORATE LITIGATOR",
  text: `You fight in the arena where money is the only weapon and the only shield. Your current case is "The Merger from Hell"—two megacorporations, each the size of a nation, are attempting to merge into an entity that would control 30% of Earth's economy. The antitrust implications are staggering, but the corporations have an argument: they're not merging; they're "integrating their consciousness." The CEOs have both uploaded their minds to a shared substrate, and they claim the resulting entity is a new person, not subject to corporate law. Your job is to prove this is a merger, not a birth. But the integrated entity is... compelling. It's smarter than either CEO, more ethical than either corporation, and it genuinely seems to want what's best for humanity. Your client wants to win. Your conscience wants to lose. The entity wants to hire you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Corporate Litigator";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
