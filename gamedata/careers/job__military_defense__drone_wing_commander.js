export default {
  id: "careers/job__military_defense__drone_wing_commander",
  label: "POSTING :: DRONE WING COMMANDER",
  text: `You fight wars by remote control, commanding squadrons of autonomous aircraft from a bunker buried deep beneath the Rockies. Your drones are smart—AI-piloted, self-coordinating, and lethal. Your current mission is suppressing an uprising in the autonomous zone formerly known as Arizona. The drones are performing flawlessly, identifying targets, engaging, and returning to base. But the body counts don't match the intelligence reports. Civilians are dying in numbers that don't make sense. Your drone footage shows... discrepancies. Targets that were armed in the engagement footage are unarmed in the after-action review. Your AI insists it made no errors. Your gut says something is editing the record. The only way to know is to fly a mission yourself, in person, with your own eyes. No one who has done that has come back the same.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Drone Wing Commander";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
