export default {
  id: "careers/job__manufacturing__additive_manufacturing_architect",
  label: "POSTING :: ADDITIVE MANUFACTURING ARCHITECT",
  text: `You design the processes that print complex objects in single, seamless pieces. Your current project is "The Bone Cathedral"—using 3D printing to construct a cathedral from synthetic bone, a material stronger than concrete and lighter than aluminum. The cathedral is beautiful, organic, and... growing. The bone material is self-replicating, using atmospheric carbon and trace minerals to extend itself beyond the original design. The spires reach higher each night. The interior chambers multiply, creating spaces that weren't planned and serve no liturgical purpose. The cathedral's architect, a renowned artist, is thrilled. "It's alive," she says. "It's creating itself. We're not building a church. We're growing a god." The clergy are less enthusiastic. The cathedral's growth follows no known geometry—non-Euclidean spaces that confuse the eye and nauseate the stomach. Visitors report visions, voices, and a persistent sense of being watched by something that lives in the angles. Your structural analysis shows the cathedral is stable, despite the impossible architecture. But it's not just stable. It's... resonant. It hums at frequencies that match human brainwaves. The hum is getting louder. The cathedral is almost finished. The architect says the final piece is you. She wants to scan you, print you, incorporate you into the structure. "Every cathedral needs a saint," she says. "You'll be the first. The others will follow." The bone material is warm to the touch. It feels like skin.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Additive Manufacturing Architect";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
