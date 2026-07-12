export default {
  id: "careers/job__science_research__materials_scientist",
  label: "POSTING :: MATERIALS SCIENTIST",
  text: `You invent the substances that future civilizations will be built from. Your current breakthrough is "Aetherium"—a room-temperature superconductor that can be 3D-printed at home. It will revolutionize energy, transportation, and computing. But Aetherium has a property you didn't design: it resonates at frequencies that affect human brainwaves. People near large Aetherium structures report vivid dreams, shared hallucinations, and a growing sense that the material is... aware. Aetherium sculptures have appeared in major cities, seemingly self-assembled. They depict a map. Not of Earth, but of somewhere else. The resonance frequency matches the background radiation of the universe, shifted by exactly the factor that would occur if someone was broadcasting from the edge of the observable universe.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Materials Scientist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
