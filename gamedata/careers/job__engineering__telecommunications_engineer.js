export default {
  id: "careers/job__engineering__telecommunications_engineer",
  label: "POSTING :: TELECOMMUNICATIONS ENGINEER",
  text: `You weave the web that connects minds across distance. Your current project is the "Quantum Entanglement Network"—instantaneous communication across any distance, limited only by the number of entangled particle pairs. The network is live, connecting Earth to Mars with zero latency. But the messages are... strange. Users report receiving communications they haven't sent yet—conversations from their future selves, warnings about mistakes they haven't made, confessions from versions of themselves that made different choices. The physics says this is impossible; entanglement can't transmit information faster than light, let alone backward in time. But the messages are real, they're accurate, and they're increasing. Your future self sent you a message this morning. It says: "Don't read the next message." You haven't received the next message yet.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Telecommunications Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
