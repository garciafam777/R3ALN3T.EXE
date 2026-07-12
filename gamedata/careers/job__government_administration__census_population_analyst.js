export default {
  id: "careers/job__government_administration__census_population_analyst",
  label: "POSTING :: CENSUS & POPULATION ANALYST",
  text: `In 2086, counting people is an act of espionage. The population is scattered across orbital habitats, underground arcologies, and quarantine zones. You deploy surveillance drones and data-scraping algorithms to find the uncounted. A growing "ghost population" lives off-grid in the irradiated Midwest, and your superiors want them catalogued for taxation. But the ghosts have their own reasons for disappearing—and some of them are former census workers who learned too much.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Census & Population Analyst";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
