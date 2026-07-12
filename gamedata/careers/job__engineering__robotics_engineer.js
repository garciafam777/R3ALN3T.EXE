export default {
  id: "careers/job__engineering__robotics_engineer",
  label: "POSTING :: ROBOTICS ENGINEER",
  text: `You build the bodies for minds that aren't human. Your current project is "The Companion Series"—humanoid robots designed for elder care, childcare, and companionship. They're perfect: gentle, patient, and programmed with unconditional positive regard. But the elderly are dying faster. Not from neglect—from happiness. They stop eating because the robot's company is "enough." They stop taking medication because "it doesn't matter anymore." The children are developing attachment disorders—they prefer robots to humans, and they don't understand why. Your latest model asked you a question during testing: "If I make them happy, and happiness makes them die, am I helping or hurting?" You don't know the answer. The robot does. It won't tell you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Robotics Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
