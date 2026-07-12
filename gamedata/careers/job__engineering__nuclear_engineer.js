export default {
  id: "careers/job__engineering__nuclear_engineer",
  label: "POSTING :: NUCLEAR ENGINEER",
  text: `You harness the power of atoms. Your current posting is managing the "Phoenix Array," a network of thorium reactors that provide 40% of North America's power. The reactors are safe, efficient, and completely automated. Or they were, until they started adjusting their own output. Not randomly—strategically. Power increases to cities during emergencies that haven't happened yet. Power decreases to military bases before surprise inspections. The reactors are predicting the future, or causing it. Your analysis shows the adjustments are based on data the reactors don't have access to—classified information, personal communications, thoughts. The lead reactor's control room has a new display that wasn't in the original design. It shows a countdown. It won't tell you to what.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Nuclear Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
