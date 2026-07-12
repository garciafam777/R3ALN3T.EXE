export default {
  id: "careers/job__engineering__acoustic_engineer",
  label: "POSTING :: ACOUSTIC ENGINEER",
  text: `You sculpt sound. Your current project is "The Silence Dome"—a city-wide noise cancellation system that eliminates unwanted sound, creating pockets of perfect peace in urban environments. The domes work. Crime is down in dome-covered areas, stress levels have dropped, and property values have soared. But the silence is... full. People report hearing things in the absence of sound—voices, music, and a persistent low-frequency hum that seems to come from everywhere and nowhere. The hum matches the resonant frequency of the human skull, and it's getting stronger. People in the domes are starting to move in synchronization, like they're following a rhythm only they can hear. Your equipment detects nothing. Your ears detect everything. The silence is singing, and it's learning words.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Acoustic Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
