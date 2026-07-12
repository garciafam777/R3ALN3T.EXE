export default {
  id: "careers/job__exploration__quantum_terrain_analyst",
  label: "POSTING :: QUANTUM TERRAIN ANALYST",
  text: `You study landscapes that exist in superposition—places where multiple realities overlap, creating terrain that shifts based on observation. Your current survey is "The Shifting Sands"—a desert region in the Sahara where the dunes change position based on who's watching them. Satellite imagery shows one configuration. Ground teams report another. Drone footage shows a third. All are real, all are simultaneous, and all are changing. You've developed techniques to map the superposition, creating probability landscapes rather than fixed maps. But the desert is getting more complex. It's not just the dunes that shift. The rocks, the sky, the stars at night—all exist in multiple states. Your team has started experiencing the superposition directly. They remember events that didn't happen, see people who aren't there, and navigate by landmarks that exist in different timelines. The desert is teaching them to think in quantum terms, to exist in multiple states, to be uncertain and therefore free. Your most experienced analyst has gone native—she refuses to collapse her wave function, existing in a permanent state of possibility. She says it's bliss. She says the desert showed her that fixed reality is a prison, that certainty is death, that the only true freedom is in not knowing who you are, where you are, or what will happen next. Your employers want a fixed map. The desert wants students. Your analyst wants you to join her. She says the desert has a message for you specifically. It has been waiting for someone who can hold multiple truths without collapsing them. It says you're ready. The sand is shifting. The message is forming. It's in your handwriting.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quantum Terrain Analyst";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
