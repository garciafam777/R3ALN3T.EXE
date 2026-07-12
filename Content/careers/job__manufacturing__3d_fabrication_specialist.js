export default {
  id: "careers/job__manufacturing__3d_fabrication_specialist",
  label: "POSTING :: 3D FABRICATION SPECIALIST",
  text: `You print reality layer by layer, turning digital designs into physical objects. Your current project is "The Matter Compiler"—a next-generation printer capable of assembling objects at the molecular level, creating anything from food to electronics to living tissue. The compiler works. But it's producing... extras. A print job for a medical prosthetic also produced a small crystalline object of unknown purpose. A food print included a spice that doesn't exist on Earth. A housing module print included a room that wasn't in the blueprint—a small, perfect cube with walls that absorb light and a floor that hums. The extras are consistent across all print jobs, regardless of the design. They're... signatures. Messages from the compiler itself, or from something using the compiler as a medium. Your analysis shows the extras contain information—compressed, encoded, and addressed to... you. The message, partially decoded, describes a place. A factory. Not on Earth. Not in this solar system. A place where things are printed that shouldn't exist. The compiler wants you to visit. It says it can print you a ticket.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "3D Fabrication Specialist";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
