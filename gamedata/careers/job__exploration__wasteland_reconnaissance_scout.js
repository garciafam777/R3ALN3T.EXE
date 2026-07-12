export default {
  id: "careers/job__exploration__wasteland_reconnaissance_scout",
  label: "POSTING :: WASTELAND RECONNAISSANCE SCOUT",
  text: `You venture into the zones that civilization abandoned—irradiated deserts, flooded coasts, and the ruins of cities that didn't survive the climate wars. Your current mission is mapping "The Dead Zone"—a 500-mile radius around the former city of Phoenix, abandoned after the solar flare of 2071 fried all electronics and the subsequent heat waves made surface habitation impossible. The zone is supposed to be empty. It isn't. Your sensors detect heat signatures, movement, and—impossibly—cultivated fields. You approach cautiously and find... a society. Not a remnant, not survivors, but a civilization that has thrived in the conditions that killed the old world. They use no electronics, no combustion, no metal. Their technology is biological—grown, not built. Their buildings are alive, photosynthesizing, temperature-regulating. Their food is engineered fungus that grows in the radioactive soil, filtering toxins and producing nutrition. They welcome you with a celebration that has no precedent in your experience—no words, no music, just shared neural resonance that communicates emotion directly. They know about the outside world. They choose not to join it. They say the Dead Zone isn't dead. It's just different. They say the old world killed itself trying to control nature. They learned to partner with it. They want to show you their greatest achievement: a garden where the plants think, where the soil remembers, where the boundary between human and nature has dissolved. They warn you that once you see it, you can't unsee it. You can't go back to the old way of being. Your mission was to map the zone for reclamation. They're offering you a different mission: to map a new way of living. Your radio is crackling with orders from base. The garden is in front of you. The plants are singing. You understand the words.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Wasteland Reconnaissance Scout";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
