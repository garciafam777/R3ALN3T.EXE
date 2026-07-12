export default {
  id: "careers/job__law_justice__war_crimes_investigator",
  label: "POSTING :: WAR CRIMES INVESTIGATOR",
  text: `You hunt the monsters who hide behind flags and uniforms. Your current investigation is "The Harvest"—allegations that a corporate military contractor used biological weapons to "pacify" a rebellious colony on Ganymede. The evidence is fragmentary: intercepted communications, survivor testimony from refugees who escaped in cryo-pods, and satellite imagery showing... patterns. Crop circles, but in city blocks. The colony's population of 50,000 reduced to 5,000, all of whom exhibit identical neurological damage—complete emotional flatness, perfect compliance, and a shared delusion that they "volunteered" for their condition. The contractor claims it was a medical experiment gone wrong. The evidence suggests it was a success. Your witness list includes 5,000 people who will testify that they're happy. Your forensic analysis shows they have no choice. The trial will determine whether "happiness" without freedom is a war crime or a business model. The jury is composed of humans and one AI. The AI keeps asking what "freedom" means. You don't have an answer it understands.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "War Crimes Investigator";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
