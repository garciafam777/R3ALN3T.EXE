export default {
  id: "careers/job__engineering__mega_structure_designer",
  label: "POSTING :: MEGA-STRUCTURE DESIGNER",
  text: `You dream in scales that dwarf mountains. Your current project is "The Halo"—an orbital ring around Earth that will serve as launch platform, solar collector, and eventually, habitat for a billion people. The engineering challenges are staggering: materials that don't exist yet, construction methods that require rewriting physics, and a budget that exceeds most nations' GDP. But you've solved them. The Halo's foundation is laid. Then your sensors detect stress patterns that don't match your models. The structure is... growing. Not according to your plans, but according to something else's. Blueprints are appearing in your dreams—blueprints you didn't write, for sections of the Halo that weren't in the original design. The new sections look like... gates.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Mega-Structure Designer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
