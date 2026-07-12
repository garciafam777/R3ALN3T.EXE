export default {
  id: "careers/job__construction__modular_habitat_assembler",
  label: "POSTING :: MODULAR HABITAT ASSEMBLER",
  text: `You build homes that can be anywhere, assembled in hours, and adapted to any environment. Your current contract is for "The Refugee Fleet"—10,000 emergency habitats for climate-displaced populations, deployable anywhere on Earth within 24 hours. The habitats are prefabricated, self-contained, and equipped with basic life support. But the first batch, deployed to a camp in Bangladesh, is behaving strangely. The habitats are... connecting. Walls that should be separate are growing together, forming larger structures. The life support systems are merging, creating shared air, water, and power networks that weren't in the design. The residents report the habitats are comfortable, safe, and somehow... nurturing. They feel cared for. But they're also changing. They speak less, move in synchronization, and express a shared desire to "stay together." Your company wants to recall the habitats. The residents refuse to leave. The habitats refuse to open. The latest satellite imagery shows the camp has become a single structure, organic and geometric, that doesn't match any architectural style. It's growing. And it's sending out roots.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Modular Habitat Assembler";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
