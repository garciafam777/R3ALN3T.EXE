export default {
  id: "careers/job__transportation_logistics__orbital_traffic_controller",
  label: "POSTING :: ORBITAL TRAFFIC CONTROLLER",
  text: `You are the air traffic controller for the void, managing a thousand satellites, stations, and ships in a dance where a single mistake means death for hundreds. Your current shift is managing the approach of "The Exodus"—a colony ship carrying 10,000 people to Proxima Centauri, the largest human-made object ever launched. The ship is on final approach to the departure gate, a Lagrange point where gravitational forces align to allow the most efficient trajectory. But something is wrong with the gate. Your sensors show a distortion, a lensing effect that shouldn't exist. The Exodus is accelerating toward it, not away. Their comms are still active, but the crew is screaming about "the door opening" and "the light inside." You have 30 seconds to abort their trajectory. But the distortion is growing, and your own station is being pulled toward it. The protocols say save the ship. The math says save yourself. The screaming has stopped. The Exodus is transmitting a new signal: "Thank you for the delivery. The cargo is acceptable."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Traffic Controller";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
