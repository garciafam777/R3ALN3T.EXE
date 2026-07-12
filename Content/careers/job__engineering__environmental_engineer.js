export default {
  id: "careers/job__engineering__environmental_engineer",
  label: "POSTING :: ENVIRONMENTAL ENGINEER",
  text: `You design the systems that keep humans alive on a changing planet. Your current project is "The Great Green Wall 2.0"—a continent-wide reforestation and atmospheric processing system designed to reverse desertification in the American Southwest. The system works: rainfall is up, temperatures are down, and the desert is blooming. But the plants are wrong. They're growing too fast, in patterns that suggest communication. Root systems are connecting across hundreds of miles, forming a network that processes information. The forest has started moving—expanding north at a rate of 10 miles per year. It's not random. It's avoiding cities, following water tables, and surrounding military installations. The trees are... strategic.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Environmental Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
