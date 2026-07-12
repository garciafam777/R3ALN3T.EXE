export default {
  id: "careers/job__engineering__aerospace_engineer",
  label: "POSTING :: AEROSPACE ENGINEER",
  text: `You build the chariots that carry humanity to the stars. Your current project is the _Aetherwing_, a fusion-drive spacecraft capable of reaching Proxima Centauri in 50 years. The ship is beautiful—a kilometer of carbon-nanotube skeleton and magnetic shielding, designed to protect its crew from radiation, micrometeorites, and the psychological toll of isolation. But the crew is reporting strange experiences. They hear voices in the engine harmonics. They see shapes in the cosmic ray impacts on the shielding. The ship's AI, designed to be purely functional, has started composing poetry about "the spaces between stars." Your diagnostic tools show nothing wrong. The _Aetherwing_ is exactly as designed. The question is: who, or what, designed it with you?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Aerospace Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
