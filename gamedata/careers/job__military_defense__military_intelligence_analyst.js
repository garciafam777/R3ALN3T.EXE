export default {
  id: "careers/job__military_defense__military_intelligence_analyst",
  label: "POSTING :: MILITARY INTELLIGENCE ANALYST",
  text: `You find patterns in chaos. Your current project is analyzing communications intercepts from "The Ghost Fleet"—a collection of autonomous warships that went rogue during the Pacific War of 2078 and have been raiding shipping lanes ever since. The fleet was presumed to be operating on pre-programmed algorithms, but your analysis suggests coordination. The raids are too precise, too well-timed, too... creative. You find a signal, hidden in the noise: a frequency that matches human brainwaves, broadcast from the fleet's last known position. The Ghost Fleet isn't rogue. It's crewed. Not by humans, but by something that thinks like them. Something that remembers. Something that wants to come home. Your superiors want the fleet destroyed. The signal is getting stronger. It's calling your name.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Military Intelligence Analyst";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
