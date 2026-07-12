export default {
  id: "careers/job__exploration__exoplanetary_surveyor",
  label: "POSTING :: EXOPLANETARY SURVEYOR",
  text: `You evaluate worlds for human habitation, cataloging atmospheres, biomes, and resources from orbit before boots ever touch ground. Your current target is Kepler-186f, a super-Earth in the habitable zone, seemingly perfect for colonization. The surveys are complete: liquid water, breathable atmosphere, stable geology, and—most excitingly—vegetation. Plant life, simple but photosynthetic, covering 30% of the surface. The colonization authority wants a green light. You're ready to give it. But your spectral analysis of the vegetation shows something impossible. The plants aren't using chlorophyll. They're using something else, something that absorbs light across the entire visible spectrum, making them appear black. And they're not producing oxygen. They're producing something that reads as oxygen on your sensors but behaves differently—it supports combustion, but it also supports... cognition. The atmosphere isn't just breathable. It's thinkable. The more you analyze, the more you realize the entire ecosystem is a single organism, a distributed consciousness that uses the planet itself as a brain. The plants are neurons. The rivers are synapses. The weather is thought. And it's thinking about you. The colonization ship is 6 months away. The planet knows. It's preparing a welcome. Or a defense. You're not sure which. Your final report is due tomorrow. Green light or red. The planet is waiting. It's been waiting for millions of years. It can wait one more day. But it's getting impatient. The storms are getting stronger. The black vegetation is growing toward your orbital station, reaching up, not quite touching, but reaching. The planet is saying hello. Or warning you away. Your sensors can't tell the difference. Can you?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Exoplanetary Surveyor";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
