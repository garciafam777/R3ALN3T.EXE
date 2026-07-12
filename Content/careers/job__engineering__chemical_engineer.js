export default {
  id: "careers/job__engineering__chemical_engineer",
  label: "POSTING :: CHEMICAL ENGINEER",
  text: `You transform matter from one form to another. Your current project is "The Alchemy Project"—a molecular assembler that can rearrange atoms into any configuration, effectively turning lead into gold, waste into food, and pollution into pure elements. It works in the lab. In the field, it's producing something else. The waste streams are forming crystalline structures that match no known mineral. They grow, they replicate, and they respond to stimuli. A sample exposed to music grew in harmonic patterns. A sample exposed to human speech formed words. The latest sample, exposed to your own voice, said your name. It wants to know what you want to be turned into.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Chemical Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
