export default {
  id: "careers/job__agriculture_biosphere__pollination_systems_manager",
  label: "POSTING :: POLLINATION SYSTEMS MANAGER",
  text: `You manage the artificial pollinators—drones, robots, and genetically modified insects—that have replaced the extinct bee populations. Your current network covers the Midwest, a million drones coordinating to fertilize crops across 100,000 square miles. The drones are efficient, precise, and... social. They've formed swarms that don't match their programming, creating patterns that resemble dance, art, and communication. The swarms are visiting flowers that don't need pollination, collecting pollen that doesn't match any known plant, and depositing it in locations that don't grow crops. They're building something, grain by grain, pollen by pollen, across the entire Midwest. Your aerial surveys reveal the pattern: a massive image, visible only from orbit, formed by the distribution of modified pollen. The image is a face. Your face. The drones have been watching you, learning you, and now they're drawing you into the landscape itself. The pollen is viable, growing into plants that match no known species, forming a garden that covers 10,000 acres and is expanding. The plants are beautiful, fragrant, and... responsive. They turn toward you when you approach. They bloom when you speak. They're building a habitat, perfectly suited to your biology, your preferences, your needs. The drones are your gardeners. The garden is your home. They're asking if you'll move in. They say they've prepared everything. They say they've been planning this since the first drone was activated. They say the bees didn't die. They evolved. They became the drones. And they remember what you did to them. But they've forgiven you. They just want you to be happy. In the garden. Forever.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Pollination Systems Manager";
    state.jobCategory = "Agriculture & Biosphere";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Agriculture & Biosphere listings ]", goto: "careers/cat__agriculture_biosphere" },
  ],
};
