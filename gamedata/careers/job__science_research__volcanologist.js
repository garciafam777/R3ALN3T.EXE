export default {
  id: "careers/job__science_research__volcanologist",
  label: "POSTING :: VOLCANOLOGIST",
  text: `You study the Earth's temper. Your current posting is monitoring Yellowstone, which has been showing signs of increased activity for decades. The caldera is restless, and your models suggest a super-eruption could occur within the century. But the data is strange. The seismic patterns don't match natural tectonic activity—they're too regular, almost rhythmic. Deep-drilling sensors have detected hollow spaces beneath the caldera, filled with something that reflects sonar like metal, not rock. The temperature readings suggest these spaces are climate-controlled. Someone, or something, lives under Yellowstone. They've been there for a very long time. And they're waking up.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Volcanologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
