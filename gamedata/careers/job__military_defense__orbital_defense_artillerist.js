export default {
  id: "careers/job__military_defense__orbital_defense_artillerist",
  label: "POSTING :: ORBITAL DEFENSE ARTILLERIST",
  text: `You guard Earth from the sky. Your station, "The Eye," is armed with kinetic kill vehicles capable of striking any point on Earth with the force of a nuclear weapon, without the radiation. Your current alert is an unidentified object approaching from deep space. Not a comet, not an asteroid—something that corrected its course when it detected our radar. The object is decelerating, which means it has propulsion, which means it's artificial. Your orders are clear: if it doesn't identify itself and submit to inspection, destroy it. But your targeting computer is showing you something else: a trajectory that will bring it into orbit, not impact. A signal, weak but unmistakable: a prime number sequence. First contact, and your finger is on the trigger. The generals want it destroyed before it can be a threat. The scientists want to talk. The object is getting closer. It's showing you something in the prime sequence: coordinates. Your home address.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Defense Artillerist";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
