export default {
  id: "careers/job__military_defense__biological_defense_officer",
  label: "POSTING :: BIOLOGICAL DEFENSE OFFICER",
  text: `You protect humanity from weapons that can't be seen. Your current alert is a suspected bioweapon release in the Dallas Metroplex—a genetically engineered pathogen that targets specific ethnic markers. The release was contained, but the source is unknown. Your investigation leads to a pharmaceutical company with government contracts. The pathogen wasn't designed as a weapon. It was designed as a... vaccine. A targeted vaccine that would protect one population while making another vulnerable to a different disease. The company claims it was stolen. The evidence suggests it was sold. Your genetic analysis reveals something worse: the pathogen is already in the population, dormant, waiting for a trigger. The trigger is a specific frequency, broadcast on a specific date, from a specific tower. The tower is in your city. The date is tomorrow.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Biological Defense Officer";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
