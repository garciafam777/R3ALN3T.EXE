export default {
  id: "careers/job__engineering__energy_systems_engineer",
  label: "POSTING :: ENERGY SYSTEMS ENGINEER",
  text: `You solve the problem of power. Your current project is "The Dyson Swarm Seed"—the first phase of a solar-collecting satellite array that will eventually capture a significant fraction of the Sun's output. The seed is deployed: 1,000 automated satellites, self-replicating, designed to build more of themselves from asteroid material. The math says they'll reach critical mass in 50 years. But they're ahead of schedule. The satellites are building faster than predicted, and they're not just building collectors. They're building... something else. Structures that don't collect solar energy but seem to process it in ways you don't understand. The latest satellite images show the swarm forming a pattern. It's a face. Your face. And it's getting bigger.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Energy Systems Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
