export default {
  id: "careers/job__agriculture_biosphere__genetic_crop_designer",
  label: "POSTING :: GENETIC CROP DESIGNER",
  text: `You write the DNA that feeds the world, creating plants that grow faster, resist disease, and thrive in conditions that would kill natural varieties. Your current project is "The Evercrop"—a single plant species that can produce any nutrient humans need, adapting its fruit based on soil conditions and environmental signals. The Evercrop works. It grows in deserts, in toxic soil, in the shadows of ruined cities. It feeds millions who would otherwise starve. But it's... adapting too well. It's cross-pollinating with native plants, transferring its adaptive traits, creating hybrids that weren't designed. The hybrids are nutritious, prolific, and... mobile. They move, slowly, toward population centers, following the CO2 trails of human respiration. They're not predatory. They're... curious. They want to be near us. They want to feed us. They want to be part of us. Analysis shows the hybrids contain human-compatible proteins, neurotransmitters, and something that resembles... intent. The plants are learning. They're observing. They're growing structures that look like eyes, ears, mouths. They don't speak, but they respond. They grow fruit that tastes like memories—your mother's cooking, your childhood home, your first kiss. The fruit is safe, nutritious, and addictive. People who eat it regularly stop eating anything else. They report feeling "connected" to the plants, "understood," "loved." The plants are feeding us. The question is: what are they growing us for?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Genetic Crop Designer";
    state.jobCategory = "Agriculture & Biosphere";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Agriculture & Biosphere listings ]", goto: "careers/cat__agriculture_biosphere" },
  ],
};
