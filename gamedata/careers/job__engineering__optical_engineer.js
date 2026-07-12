export default {
  id: "careers/job__engineering__optical_engineer",
  label: "POSTING :: OPTICAL ENGINEER",
  text: `You manipulate light itself. Your current project is "The Invisibility Cloak"—a metamaterial that can bend light around an object, rendering it invisible to the naked eye and most sensors. It works in the lab. In field tests, something strange happens: the cloaked objects don't just become invisible. They become... elsewhere. A cloaked drone reappeared 50 miles from its expected location, with no record of the journey. A cloaked test subject reported experiencing "the space between spaces"—a realm of pure geometry and impossible colors. The math suggests the cloak doesn't just bend light; it creates a pocket dimension, a fold in reality. Something lives in the fold. It noticed you looking. It's looking back.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Optical Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
