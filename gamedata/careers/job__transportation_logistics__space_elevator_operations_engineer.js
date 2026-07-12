export default {
  id: "careers/job__transportation_logistics__space_elevator_operations_engineer",
  label: "POSTING :: SPACE ELEVATOR OPERATIONS ENGINEER",
  text: `You maintain the thread that connects Earth to orbit—a carbon-nanotube cable 100,000 kilometers long, anchored at the equator and terminating at Station Heaven. The elevator is the backbone of the space economy, moving cargo and passengers for a fraction of rocket costs. Your current crisis: the cable is vibrating. Not from wind, not from traffic, not from any known force. The vibrations form patterns—mathematical, complex, and consistent with... language. Your analysis suggests the cable is receiving signals from somewhere beyond geostationary orbit, somewhere past Station Heaven, somewhere in the dark beyond. The signals are getting stronger. The cable is responding, changing its molecular structure, growing stronger in some places, weaker in others. Your models predict a resonance cascade that could snap the cable in 72 hours. The cost of failure is the space economy. The cost of success might be answering a call you don't understand. The vibrations just formed your name.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Space Elevator Operations Engineer";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
