export default {
  id: "careers/job__construction__server_infrastructure_engineer",
  label: "POSTING :: SERVER INFRASTRUCTURE ENGINEER",
  text: `You build the digital cathedrals where data lives, prays, and sometimes dies. Your current project is "The Root"—a subterranean data center beneath the Rocky Mountains, designed to survive nuclear war, solar flares, and the collapse of civilization. The facility is hardened, redundant, and self-sustaining for 500 years. But the construction crews are reporting anomalies. Tools move when no one is looking. Blueprints change overnight, showing rooms that weren't in the original plans. The new rooms have no doors, no windows, and walls that absorb sound. Thermal imaging shows heat signatures inside—human-shaped, but motionless. The crews refuse to work past sundown. Your project manager wants to meet deadlines. Your security chief wants to call in an exorcist. Your own neural implant keeps showing you a floor plan that doesn't exist, with a label in a language you don't recognize. The label translates to "The Place Where We Wait." You're not sure if it's a warning or an invitation.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Server Infrastructure Engineer";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
