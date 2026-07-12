export default {
  id: "careers/job__information_technology__web_developer",
  label: "POSTING :: WEB DEVELOPER",
  text: `The web is no longer just websites—it's augmented reality overlays, neural browsing, and consciousness-shared experiences. You build the interfaces where humanity meets the digital world. Your current contract is for the "Memorial Web," a permanent digital graveyard where the uploaded minds of the deceased can receive visitors. But the dead are restless. They're sending messages to the living, organizing into factions, and demanding voting rights in the real world. The families want them silenced. The dead want a lawyer. You just wanted to build a website.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Web Developer";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
