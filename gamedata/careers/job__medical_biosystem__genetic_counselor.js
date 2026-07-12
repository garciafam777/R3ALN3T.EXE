export default {
  id: "careers/job__medical_biosystem__genetic_counselor",
  label: "POSTING :: GENETIC COUNSELOR",
  text: `You guide people through the maze of their own DNA. Your current client is a couple who want to ensure their child has "optimal" genetics—intelligence, health, longevity, beauty. The technology exists to edit every gene. But your analysis reveals something impossible: the couple's DNA contains sequences that don't match any known genetic code. They're not human. Not entirely. The sequences activate under specific conditions, rewriting the genome in real-time. The couple doesn't know. They've lived normal lives, unaware that their bodies are... waiting. For what, you don't know. But if you edit their child's DNA, you might remove the sequences. Or you might trigger them. Either way, you'll be deciding the fate of something that doesn't know it exists yet.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Genetic Counselor";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
