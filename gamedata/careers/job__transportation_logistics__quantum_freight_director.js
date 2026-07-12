export default {
  id: "careers/job__transportation_logistics__quantum_freight_director",
  label: "POSTING :: QUANTUM FREIGHT DIRECTOR",
  text: `You manage the flow of goods across distances that shouldn't be traversable. Your current operation is "The Entanglement Express"—using quantum teleportation to move cargo between Earth and the lunar colonies instantaneously. The technology works for inanimate objects. Living things... arrive different. Not dead, not damaged, just... altered. A shipment of seeds arrived and grew into plants that photosynthesize moonlight. A shipment of electronics arrived with circuits that process information in ways their designers don't understand. Your latest shipment was a cryo-pod containing a human colonist. She arrived alive, healthy, and convinced she was on Earth, in a house that burned down 30 years ago. She described the fire in detail, including things she couldn't have known. She wasn't on the manifest as a colonist. She was listed as "personal effects." The sender wants her back. She doesn't want to go. She says she's finally home.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quantum Freight Director";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
