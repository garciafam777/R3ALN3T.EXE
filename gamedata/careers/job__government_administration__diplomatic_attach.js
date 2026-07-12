export default {
  id: "careers/job__government_administration__diplomatic_attach",
  label: "POSTING :: DIPLOMATIC ATTACHÉ",
  text: `Earth's nations still exist, but they share power with orbital colonies, Martian settlements, and corporate nation-states. You are the bridge between the old world and the new, stationed at the Lunar Embassy or the underwater Atlantic Union headquarters. Your role is part negotiator, part spy. The Europa Collective wants trade rights; the Pan-Asian Consortium wants mining concessions on Luna. Every handshake hides a blade. Your starting state determines which alliance you were born into—and which ones will never trust you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Diplomatic Attaché";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
