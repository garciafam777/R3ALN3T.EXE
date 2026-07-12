export default {
  id: "careers/job__science_research__climate_engineer",
  label: "POSTING :: CLIMATE ENGINEER",
  text: `You fix the sky. After decades of failed diplomacy, humanity has turned to direct intervention: orbital mirrors that reflect sunlight, atmospheric processors that scrub CO2, and ocean seeding that accelerates carbon absorption. You manage the North American Atmospheric Processor Array, a continent-wide network of towers that filters the air. The processors are working—global temperatures are stabilizing. But the filtered air is changing people. Cities near the processors report increased empathy, reduced aggression, and a shared dream of a forest that doesn't exist on Earth. Your air quality reports show a compound that shouldn't be there, something the filters are adding, not removing. It's in your lungs too. You feel... calmer than you should.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Climate Engineer";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
