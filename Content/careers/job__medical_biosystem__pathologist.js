export default {
  id: "careers/job__medical_biosystem__pathologist",
  label: "POSTING :: PATHOLOGIST",
  text: `You speak for the dead. Your current autopsy is on a body that shouldn't exist—a humanoid figure found in the wreckage of a crashed unidentified aircraft in the Nevada desert. The body is human, genetically identical to a missing person from 1987. But the organs are wrong: additional chambers in the heart, a second liver, and a brain that shows signs of extensive modification. The modifications aren't surgical—they're grown. The body was designed, not born. The missing person from 1987 was 12 years old. This body is biologically 25. The timeline doesn't work unless... they were taken. Modified. Grown. Released. The body has a tattoo: coordinates. In the Nevada desert. 50 miles from where it was found. Your supervisor tells you to stop asking questions. The body opens its eyes.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Pathologist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
