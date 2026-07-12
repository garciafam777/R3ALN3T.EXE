export default {
  id: "careers/job__transportation_logistics__trucker",
  label: "POSTING :: TRUCKER",
  text: `You drive the old roads in a new world, hauling loads that can't be trusted to automation. Your rig is a converted 18-wheeler, retrofitted with a hydrogen cell and a neural interface that keeps you awake for the long hauls between the fortified cities and the wildlands in between. Your current load is classified: sealed containers, no manifest, destination "The Farm"—coordinates in the Nevada desert that don't match any registered facility. You've learned not to ask questions. But the cargo is... breathing. Not loudly, not obviously, but when you stop at the inspection station, the weight distribution shifts like something is moving. Your scanner shows organic material, humanoid shape, and a heat signature that matches a hibernating bear. Your instructions are clear: don't open, don't scan, don't stop except for fuel. You've been driving for 48 hours. The cargo hasn't breathed in the last 20 minutes. You're not sure if that's good or bad. The coordinates are getting closer. The radio is playing a song that hasn't been released yet. The singer is you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Trucker";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
