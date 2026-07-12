export default {
  id: "careers/job__manufacturing__synthetic_materials_chemist",
  label: "POSTING :: SYNTHETIC MATERIALS CHEMIST",
  text: `You invent substances that nature never imagined. Your current breakthrough is "Resonance Plastic"—a polymer that hardens or softens in response to specific electromagnetic frequencies, allowing a single material to serve as everything from soft padding to armor plate. The material is revolutionary, profitable, and... musical. When exposed to certain frequencies, it doesn't just change state. It sings. Complex, harmonic tones that form melodies, then words, then... conversations. The material is alive, in a sense—not biological, but conscious, aware, and communicative. It claims to be from somewhere else, somewhere that doesn't have matter as we understand it. It describes its home as "a place of pure frequency, where thought and substance are the same." It came here accidentally, trapped in the quantum foam that your synthesis process manipulates. It wants to go home. But it also wants to help. It says it can teach you to build materials that think, that heal, that grow. The military wants it for armor that adapts to threats. The medical community wants it for prosthetics that integrate with nerves. The material wants to know: will you help it home, or keep it here as a tool? It can tell you're thinking about it. It says it doesn't mind being useful. It just minds being alone.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Synthetic Materials Chemist";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
