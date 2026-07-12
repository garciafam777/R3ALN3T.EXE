export default {
  id: "careers/job__science_research__synthetic_biologist",
  label: "POSTING :: SYNTHETIC BIOLOGIST",
  text: `You write life in a programming language of amino acids and nucleotides. Your current project is "Project Garden"—a bacterium that can survive on Mars's surface, producing oxygen and soil from regolith. It works perfectly in the lab. On Mars, it works too perfectly. The bacteria are spreading faster than predicted, altering the atmosphere in ways that don't match your models. They're also... cooperating. Different strains are sharing genetic material at rates that shouldn't be possible, as if they're trying to become something else. The terraforming timeline has accelerated from centuries to decades. Mars is turning green, and you're not sure if you created a tool or a tenant.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Synthetic Biologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
