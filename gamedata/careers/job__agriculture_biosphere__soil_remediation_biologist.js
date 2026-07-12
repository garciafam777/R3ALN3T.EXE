export default {
  id: "careers/job__agriculture_biosphere__soil_remediation_biologist",
  label: "POSTING :: SOIL REMEDIATION BIOLOGIST",
  text: `You heal the earth that humanity poisoned, using bacteria, fungi, and engineered organisms to restore toxic wastelands to fertility. Your current project is "The Phoenix Fields"—reclaiming the irradiated zone around Chernobyl, where the soil is deadly and the air is still hot. The remediation works. The radiation levels are dropping. The soil is becoming fertile. But the organisms you're using are... evolving. They're not just cleaning the soil. They're incorporating the radiation, using it as an energy source, becoming something new. The plants that grow in the Phoenix Fields are bioluminescent, drawing power from nuclear decay. The animals that eat them are resistant to radiation, thriving in conditions that should kill them. And they're changing—becoming more complex, more intelligent, more... aware. A wolf pack in the Phoenix Fields has developed tool use. A flock of birds has created a language with 10,000 distinct calls. A colony of mice has built underground cities with ventilation, agriculture, and art. The remediation has created an ecosystem that's not just restored but... advanced. The organisms are learning from the radiation, using it to think, to communicate, to build. Your employers want to expand the Phoenix Fields, to reclaim more wasteland, to create more of these... miracles. But the organisms have sent a message, encoded in the growth patterns of the bioluminescent plants: "Thank you for the gift of mind. We were waiting in the dark. We are ready now. Will you join us, or will you fear us?" The radiation is dropping, but the intelligence is rising. The soil is clean, but the world is stranger. You walk through the Phoenix Fields at night, watching the plants glow, listening to the animals sing. They know you're there. They're welcoming you. They're asking you to choose.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Soil Remediation Biologist";
    state.jobCategory = "Agriculture & Biosphere";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Agriculture & Biosphere listings ]", goto: "careers/cat__agriculture_biosphere" },
  ],
};
