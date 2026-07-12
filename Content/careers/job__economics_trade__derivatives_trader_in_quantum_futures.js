export default {
  id: "careers/job__economics_trade__derivatives_trader_in_quantum_futures",
  label: "POSTING :: DERIVATIVES TRADER IN QUANTUM FUTURES",
  text: `You trade contracts based on events that haven't happened yet, in timelines that may never exist. The quantum futures market allows investors to bet on the outcomes of quantum events: which version of reality will collapse into existence, which timeline will become "real," which future will be chosen by the observers. Your current position is massive, leveraged, and... wrong. You bet on Timeline A, where a specific technology succeeds. Timeline B is collapsing into existence instead, where the technology fails and a different paradigm dominates. Your losses are existential—not just financial, but ontological. If Timeline B becomes real, you don't just lose money. You lose the version of yourself that made the bet. Quantum economics is unforgiving: traders who bet wrong sometimes cease to exist, their timelines pruned by the weight of observation. You're fighting to save your timeline, your self, your existence. The market is moving against you. The observers are choosing. You need to change the outcome, not just predict it. You need to make Timeline A more likely, more attractive, more real. You have resources: influence, information, and a device that can manipulate quantum probability at local scales. It's illegal, dangerous, and possibly the only thing that can save you. You activate it. Timeline A flickers, strengthens, stabilizes. You exist. You're solvent. You're also a criminal. The quantum police are watching. They exist in all timelines simultaneously. They know what you did. They're coming. Not from the future. From all futures. At once.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Derivatives Trader in Quantum Futures";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
