export default {
  id: "careers/job__military_defense__military_quantum_strategist",
  label: "POSTING :: MILITARY QUANTUM STRATEGIST",
  text: `You plan battles that exist in superposition—fought, not fought, and both simultaneously until observed. Your current operation is "Schrodinger's Shield," a defensive strategy that uses quantum entanglement to coordinate forces across light-years of separation. The theory is sound: entangled commanders can share information instantaneously, making coordinated maneuvers impossible to intercept or predict. But the first field test reveals a problem. The entangled commanders are experiencing each other's realities. A general on Earth feels the Martian dust in her lungs. A colonel on Mars tastes the coffee from Earth's command center. And they're not just sharing sensations—they're sharing decisions. One commander's choice becomes the other's, retroactively. The battle was fought yesterday and tomorrow. The outcome is simultaneously victory and defeat. Your job is to report the results. But which results? And to whom?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Military Quantum Strategist";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
