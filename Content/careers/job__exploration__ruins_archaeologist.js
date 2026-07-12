export default {
  id: "careers/job__exploration__ruins_archaeologist",
  label: "POSTING :: RUINS ARCHAEOLOGIST",
  text: `You excavate the remains of civilizations that rose and fell while humanity was still learning to farm. Your current dig is in the Arabian Desert, where satellite imaging revealed geometric patterns that predate human civilization by 100,000 years. The ruins are vast—a city that covered 100 square kilometers, built by beings who weren't human, weren't mammalian, and may not have been biological at all. The structures are crystalline, grown rather than built, and they resonate at frequencies that affect human consciousness. Your team reports shared visions when they touch the ruins: a world of light and geometry, inhabited by beings of pure mathematics, who built this city as a... museum. A repository of knowledge, waiting for someone evolved enough to understand it. The ruins are teaching. Every structure contains information, encoded in its geometry, its resonance, its relationship to the stars. Your team is learning faster than any educational system could teach them. They're solving problems that have stumped physicists for centuries, developing technologies that shouldn't be possible, and speaking a language that has no words—only mathematical relationships. Your employers want the technology. The ruins want to complete their purpose. They were built to teach. To uplift. To prepare a species for membership in a community that spans the galaxy. The final lesson is approaching. It requires a sacrifice—not of life, but of limitation. The ruins want to remove the barriers that keep humans from thinking clearly, from perceiving truly, from knowing what they could be. Your team is ready. They're asking if you are. The crystals are humming. The lesson is about to begin.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Ruins Archaeologist";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
