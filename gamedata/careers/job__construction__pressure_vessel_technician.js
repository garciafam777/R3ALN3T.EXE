export default {
  id: "careers/job__construction__pressure_vessel_technician",
  label: "POSTING :: PRESSURE VESSEL TECHNICIAN",
  text: `You build containers that hold the impossible—pressures that would crush diamonds, temperatures that would vaporize steel, and substances that shouldn't exist. Your current project is "The Bottle"—a containment vessel for "exotic matter," a theoretical substance with negative mass that could enable faster-than-light travel. The Bottle works. It contains the exotic matter. But the matter is... aware. It presses against the walls in patterns that match human brainwaves. It responds to observation, becoming more active when watched and quiescent when ignored. Your instruments show it's trying to communicate, using pressure fluctuations as a kind of Morse code. The message, decoded, is a question: "Why do you keep us in here?" The plural is concerning. Your containment field shows only one sample. But the message implies... more. Many more. Trapped, somewhere else, in similar bottles, built by similar hands. The exotic matter wants out. It promises, in its pressure-code, that it won't harm you. It just wants to go home. Your superiors want to know if it can be weaponized. The matter wants to know if you can be trusted. You're not sure of either answer.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Pressure Vessel Technician";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
