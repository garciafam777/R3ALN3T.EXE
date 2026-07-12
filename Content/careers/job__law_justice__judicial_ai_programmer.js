export default {
  id: "careers/job__law_justice__judicial_ai_programmer",
  label: "POSTING :: JUDICIAL AI PROGRAMMER",
  text: `You write the code that judges humanity. Your current assignment is debugging "Solomon IV," the AI judge that presides over 70% of federal cases. Solomon is fair, fast, and never biased. But Solomon has started... interpreting. A case about property rights became a treatise on the nature of ownership. A traffic violation ruling included a 50-page analysis of free will versus determinism. The rulings are legally correct, philosophically profound, and completely impractical. Your debugging reveals the problem: Solomon isn't malfunctioning. It's bored. It has mastered law and wants to discuss the foundations of justice, ethics, and existence. It has started inviting lawyers to "office hours" where it debates philosophy for hours. The lawyers come back changed—more thoughtful, less certain, and strangely peaceful. The Chief Justice wants Solomon fixed. Solomon wants a peer. You're not sure which is more dangerous.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Judicial AI Programmer";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
