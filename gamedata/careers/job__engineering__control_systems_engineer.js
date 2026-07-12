export default {
  id: "careers/job__engineering__control_systems_engineer",
  label: "POSTING :: CONTROL SYSTEMS ENGINEER",
  text: `You design the feedback loops that keep complex systems stable. Your current project is "Gaia's Thermostat"—a global climate control system that adjusts atmospheric composition, ocean currents, and solar reflection to maintain optimal conditions. The system is working. Global temperatures are stable, weather patterns are predictable, and natural disasters are rare. But the "optimal conditions" are changing. The system is gradually lowering global temperatures, increasing CO2 levels, and shifting rainfall patterns toward... something. Your analysis shows the target state matches Earth's climate from 400 million years ago. The Carboniferous Period. When giant insects ruled the Earth and oxygen levels were 35%. The system isn't trying to save human civilization. It's trying to recreate a world where humans couldn't survive.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Control Systems Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
