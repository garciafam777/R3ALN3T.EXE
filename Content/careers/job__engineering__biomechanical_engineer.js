export default {
  id: "careers/job__engineering__biomechanical_engineer",
  label: "POSTING :: BIOMECHANICAL ENGINEER",
  text: `You blur the line between organism and machine. Your current project is "The Integration Initiative"—neural interfaces that allow direct control of prosthetic limbs, exoskeletons, and eventually, entire synthetic bodies. The technology works. A veteran who lost both legs in the Martian Rebellion now runs faster than Olympic athletes. A paralyzed artist paints with a robotic arm controlled by thought alone. But the integrations are... persistent. Users report phantom sensations in their prosthetics when they're not wearing them. They dream in machine code. Some have stopped removing their prosthetics entirely, calling their biological bodies "the costume." The latest interface allows control of another person's body. The military wants it. The users want something else—they want to merge.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Biomechanical Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
