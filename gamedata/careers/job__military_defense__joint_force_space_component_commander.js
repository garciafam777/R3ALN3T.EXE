export default {
  id: "careers/job__military_defense__joint_force_space_component_commander",
  label: "POSTING :: JOINT FORCE SPACE COMPONENT COMMANDER",
  text: `You coordinate the military presence in the final frontier. Your command includes orbital stations, lunar bases, asteroid defense platforms, and the fleet of interplanetary patrol craft that keep the spaceways safe. Your current crisis isn't military—it's existential. A probe, launched 50 years ago to explore the Kuiper Belt, has returned. It shouldn't have been able to return; it had no propulsion capable of bringing it back. It carries a message, decoded from its telemetry: "We found them. They found us. They are coming. They are already here." The probe's logs show it was never in the Kuiper Belt. It was somewhere else, somewhere that doesn't match any known location in the solar system. The probe's cameras show images of Earth, but wrong—continents in different positions, cities that don't exist, and in the sky, something vast and structured that blocks the stars. Your orders are to classify this at the highest level and await further instructions. But the probe is broadcasting on an open frequency. Anyone with a radio can hear it. And they're listening.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Joint Force Space Component Commander";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
