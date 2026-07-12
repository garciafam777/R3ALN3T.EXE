export default {
  id: "careers/job__military_defense__orbital_marine",
  label: "POSTING :: ORBITAL MARINE",
  text: `You fight in the void where there is no up or down, only the enemy and the endless dark. Your current deployment is guarding "Fort Liberty," a military station in geostationary orbit that protects Earth's satellite infrastructure. The enemy isn't who you expected. Not Russians, not Chinese, not corporate mercenaries. Something is attacking satellites—something that leaves no debris, no heat signature, no trace except the silence where a billion-dollar asset used to be. Your patrol spotted it once: a shape that wasn't a ship, wasn't a drone, wasn't anything with thrusters. It moved like it was swimming through space. Your targeting computers couldn't lock on. Your sergeant ordered you to fire anyway. The rounds passed through it. Then it passed through him. He's still alive. He just isn't... there anymore.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Marine";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
