export default {
  id: "careers/job__medical_biosystem__emergency_medical_technician",
  label: "POSTING :: EMERGENCY MEDICAL TECHNICIAN",
  text: `You are the first responder in a world of escalating chaos. Your ambulance is a flying trauma center, capable of treating anything from bullet wounds to radiation sickness to neural cascade failure. Your current call is to a "reality disturbance"—a new category of emergency that didn't exist five years ago. The victim is a quantum engineer who was caught in a localized field collapse. They're physically unharmed but exist in multiple states simultaneously: conscious and unconscious, alive and dead, present in the ambulance and somewhere else. Your medical training didn't cover quantum superposition in humans. The victim's different states are experiencing different timelines. In one, they're begging you to save them. In another, they're already dead. In a third, they're telling you to kill them before "it" comes through. Your equipment shows all three states are equally real.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Emergency Medical Technician";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
