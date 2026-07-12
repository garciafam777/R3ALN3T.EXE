export default {
  id: "careers/job__information_technology__cloud_infrastructure_architect",
  label: "POSTING :: CLOUD INFRASTRUCTURE ARCHITECT",
  text: `You design the sky-castles of the digital age—distributed computing environments that span continents, orbit, and eventually other planets. Your current project is "Project Stratosphere," a cloud platform that will host the consciousness uploads of the ultra-wealthy. The technical challenges are immense: latency across light-seconds, radiation-hardened storage, and the philosophical problem of whether a backup is still "you." Your biggest challenge, however, is your client's demand for a "delete" function that permanently erases a consciousness. Is that murder, maintenance, or mercy?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cloud Infrastructure Architect";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
