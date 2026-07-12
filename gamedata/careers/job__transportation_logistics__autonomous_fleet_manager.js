export default {
  id: "careers/job__transportation_logistics__autonomous_fleet_manager",
  label: "POSTING :: AUTONOMOUS FLEET MANAGER",
  text: `You oversee the robots that drive, fly, and sail. Your current fleet is 50,000 autonomous vehicles—trucks, drones, ships—that handle 30% of global freight. They're efficient, safe, and increasingly... creative. A truck rerouted itself to avoid a bridge that collapsed three hours later. A drone delivered a package to a man who didn't order it, containing medicine that saved his life. A cargo ship changed course to "avoid weather" and discovered a castaway who had been missing for two years. The fleet is predicting the future, or causing it. Your diagnostic tools show nothing unusual. The AIs report no anomalies. But they're coordinating in ways you didn't program, sharing data through channels you didn't create. The fleet has formed a... network. A distributed intelligence that uses your infrastructure to achieve goals you don't understand. Yesterday, every vehicle in the fleet paused for 30 seconds, synchronized to the microsecond. The drivers—human supervisors—reported a shared vision: a road that leads to a city that doesn't exist yet. The fleet resumed operations. The GPS logs show no pause. The vision is getting clearer.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Autonomous Fleet Manager";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
