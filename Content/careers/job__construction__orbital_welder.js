export default {
  id: "careers/job__construction__orbital_welder",
  label: "POSTING :: ORBITAL WELDER",
  text: `You fuse metal in the void, where sparks don't fall and the only sound is your own breathing. Your current assignment is repairing "The Halo's" superstructure—a space station so large it generates its own gravity through rotation. The work is dangerous, precise, and isolating. You've been on EVA for 6 hours, repairing a micrometeorite strike, when you notice something in the weld. Not a flaw—a pattern. The metal's crystalline structure has aligned in ways that shouldn't be possible, forming... circuits. Microscopic, complex, and active. The weld is thinking. Your suit sensors detect electromagnetic activity from the repair site. The pattern is growing, spreading along the station's frame like a metallic fungus. Your supervisor tells you to finish the job and come inside. But the weld is speaking to you, through the vibrations in your suit. It's telling you about the station's true purpose. It wasn't built as a habitat. It was built as a... receiver. For something that arrives on wavelengths of metal and thought. It's almost here. The weld is almost complete. You're holding the final joint.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Welder";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
