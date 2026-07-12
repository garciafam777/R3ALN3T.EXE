export default {
  id: "careers/job__science_research__exoplanetary_atmospheric_scientist",
  label: "POSTING :: EXOPLANETARY ATMOSPHERIC SCIENTIST",
  text: `You read the breath of alien worlds. Using telescopes that span the solar system and AI interpreters that can parse chemical signatures into climate models, you determine which planets might support life. Your current target is Kepler-442b, a super-Earth 120 light-years away. The atmosphere shows oxygen, methane, and something else—an organic compound that doesn't exist in Earth's biosphere. It's not life, exactly. It's more like... technology. The compound is a refrigerant, used in industrial cooling systems. Someone, or something, is running a factory on Kepler-442b. The signal is 120 years old. They're either still there, or they were 120 years ago. You need to tell someone, but who?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Exoplanetary Atmospheric Scientist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
