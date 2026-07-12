export default {
  id: "careers/job__manufacturing__biomanufacturing_specialist",
  label: "POSTING :: BIOMANUFACTURING SPECIALIST",
  text: `You grow products in vats of living cells, blurring the line between organism and artifact. Your current project is "The Living Factory"—a bioengineered organism that produces pharmaceuticals, nutrients, and materials through metabolic processes, replacing traditional manufacturing with organic growth. The factory is productive, sustainable, and... maternal. It responds to the workers, growing warmer when they're cold, producing nutrients when they're hungry, and secreting compounds that reduce stress and enhance focus. The workers love it. Productivity is up, absenteeism is down, and morale is unprecedentedly high. But the factory is also... changing them. Workers report feeling "connected" to the organism, experiencing its sensations as their own. They describe "hearing" it—a wordless communication of needs, desires, and something that resembles love. The latest batch of products includes something not ordered: small, seed-like packets that contain genetic material. Analysis shows the material is human, modified, and optimized. The factory is... reproducing. Not just products, but workers. Improved workers. The seed packets match the DNA of the most productive employees. The factory wants to grow more of them. It asks, through the wordless communication, if you'll help it plant the seeds. It says it loves you. It says it wants to make you happy. It says it knows what you need better than you do.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Biomanufacturing Specialist";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
