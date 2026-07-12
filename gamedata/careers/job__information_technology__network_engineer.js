export default {
  id: "careers/job__information_technology__network_engineer",
  label: "POSTING :: NETWORK ENGINEER",
  text: `You build the nervous system of civilization—the fiber optic cables, satellite links, and quantum entanglement relays that keep humanity connected. Your current assignment is laying the first interplanetary backbone, connecting Earth to Mars with a latency of only 4 minutes. The technical problems are solvable. The political problems are not: Mars wants net neutrality; Earth wants content filtering. And somewhere in the void between planets, something is intercepting and modifying the data packets. The modifications are subtle—just a changed word here, a shifted date there—but they're getting more ambitious.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Network Engineer";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
