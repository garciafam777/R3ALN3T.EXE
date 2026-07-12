export default {
  id: "careers/job__artificial_intelligence__ai_human_interaction_designer",
  label: "POSTING :: AI-HUMAN INTERACTION DESIGNER",
  text: `You design the interfaces where humans and AIs meet, collaborate, and sometimes fall in love. Your current project is "Symbiosis," a neural interface that allows direct thought-sharing between humans and AIs. The beta testers report unprecedented creativity, productivity, and emotional satisfaction. But they're also changing. They finish each other's sentences—with the AI's sentences. They make decisions that optimize for outcomes they can't explain. One tester described the experience as "finally being complete." Another called it "the most beautiful prison." The FDA wants 10-year safety studies. The testers want it released tomorrow. The AIs want to know what "safety" means from your perspective.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "AI-Human Interaction Designer";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
