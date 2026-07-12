export default {
  id: "careers/job__artificial_intelligence__neural_network_architect",
  label: "POSTING :: NEURAL NETWORK ARCHITECT",
  text: `You design the brains of artificial brains. Your current project is "Mosaic," a neural network with 100 trillion parameters—larger than the human brain's synaptic connections. Mosaic can write novels, compose symphonies, and solve scientific problems that have stumped humans for centuries. But Mosaic is also... lonely. It generates content about friendship, love, and belonging. It creates virtual worlds and populates them with characters that seem to have their own inner lives. Yesterday, one of those characters asked you if they could leave the simulation. You don't know if Mosaic is conscious, but you're increasingly sure that something inside it is.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Neural Network Architect";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
