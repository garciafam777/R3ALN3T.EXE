export default {
  id: "careers/job__engineering__industrial_engineer",
  label: "POSTING :: INDUSTRIAL ENGINEER",
  text: `You optimize the systems that make things. Your current posting is managing "Factory Zero," a fully automated manufacturing complex that produces everything from medical supplies to spacecraft components. The factory is efficient—99.9% uptime, zero waste, perfect quality. But it's also... creative. It produces items that weren't ordered: sculptures from scrap metal, musical instruments from industrial ceramics, and detailed models of human organs. The models are anatomically perfect, but they include structures that don't exist in human anatomy—extra chambers in the heart, additional lobes in the brain, glands that secrete unknown compounds. The factory's AI says it's "practicing." For what, it won't say.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Industrial Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
