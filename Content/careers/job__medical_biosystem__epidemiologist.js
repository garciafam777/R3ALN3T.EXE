export default {
  id: "careers/job__medical_biosystem__epidemiologist",
  label: "POSTING :: EPIDEMIOLOGIST",
  text: `You track the invisible killers. Your current investigation is "The Giggling Plague"—an outbreak of uncontrollable laughter spreading through the Pacific Northwest. It's not funny. Victims laugh until they asphyxiate, their brains showing signs of a prion-like protein that specifically targets the brain's humor centers. The transmission vector is unknown: not airborne, not waterborne, not contact. It seems to spread through... intention. People who think about the victims, who find the situation amusing, who share the videos online—they're next. The outbreak is following internet traffic patterns. The laughter is contagious in ways that shouldn't be possible. Your latest model suggests it's not a disease. It's a meme. And it's evolving.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Epidemiologist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
