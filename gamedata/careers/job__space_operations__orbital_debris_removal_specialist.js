export default {
  id: "careers/job__space_operations__orbital_debris_removal_specialist",
  label: "POSTING :: ORBITAL DEBRIS REMOVAL SPECIALIST",
  text: `You clean up the mess humanity made in space, tracking and removing the thousands of dead satellites, spent rocket stages, and fragments of collisions that threaten active spacecraft. Your current target is "The Cluster"—a dense collection of debris in geostationary orbit that has formed something unexpected. The debris isn't just orbiting randomly. It's... organized. The pieces have arranged themselves into a structure, held together by forces that shouldn't exist, forming a shape that resembles... a gate. A ring, 100 meters across, made of twisted metal and shattered solar panels, that emits a faint electromagnetic hum. Your approach triggers a response. The gate activates, not mechanically but... dimensionally. Space bends around it, light distorts, and for a moment, you see through it. To somewhere else. A place that isn't Earth orbit, isn't the solar system, isn't anywhere in known space. It's a station, vast and ancient, populated by figures that look human but aren't, moving through corridors that extend in directions that don't match Euclidean geometry. They notice you. They wave. They smile. They look... welcoming. The gate closes. You're back in normal space, your ship's instruments showing a 3-second gap in the timeline. The debris is still there, still organized, still humming. Your mission was to remove it. But removal would mean destroying the gate, severing the connection, possibly forever. Your employers want the debris cleared. The figures want... visitors. You're not sure what you want. But you can't stop thinking about the station, the figures, the corridors that went somewhere impossible. You dream about it, every night, and in your dreams, you're walking those corridors, meeting those figures, learning things that change how you see everything. The debris is waiting. The gate is ready. Your ship has the tools to destroy it or to... stabilize it. To make the connection permanent. To build a bridge between here and there. The choice is yours. The figures are waiting. And in your dreams, they're saying: "Hurry. We don't have much time. Neither do you."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Debris Removal Specialist";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
