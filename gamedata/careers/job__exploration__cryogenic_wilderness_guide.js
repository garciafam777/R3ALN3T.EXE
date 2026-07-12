export default {
  id: "careers/job__exploration__cryogenic_wilderness_guide",
  label: "POSTING :: CRYOGENIC WILDERNESS GUIDE",
  text: `You lead expeditions into the frozen regions that cover 40% of Earth's landmass in 2086—Antarctica, Greenland, and the new ice sheets that formed after the climate tipping points. Your current expedition is crossing the Ross Ice Shelf, mapping the new geography created by the collapse of the West Antarctic Ice Sheet. The journey is brutal, beautiful, and increasingly strange. Your team has found structures in the ice—not human, not recent, and not natural. Geometric shapes, perfect angles, materials that don't match any known composition. They're melting out of the glacier, emerging as the ice retreats. The structures are getting more numerous as you travel deeper. They're also getting... active. Your thermal imaging shows heat signatures inside, despite the -50°C exterior. Your ground-penetrating radar shows hollow spaces, corridors, chambers. Your seismic sensors detect rhythmic vibrations, like a heartbeat, from the largest structure. It's not a ruin. It's a machine. Or a body. Or both. The ice has preserved it for millions of years. The warming has awakened it. Your team wants to enter. Your survival instincts say run. The structure has noticed you. The heartbeat is speeding up. The ice is cracking in patterns that match your footsteps. You're not exploring the wilderness anymore. The wilderness is exploring you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cryogenic Wilderness Guide";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
