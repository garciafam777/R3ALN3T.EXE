export default {
  id: "careers/job__education__memory_preservation_educator",
  label: "POSTING :: MEMORY PRESERVATION EDUCATOR",
  text: `You teach people to curate their own minds in an age where memory is editable, deletable, and marketable. Your current workshop is "The Authentic Self"—helping clients distinguish between genuine memories and implanted ones, between lived experience and manufactured nostalgia. The work is delicate, psychological, and increasingly impossible. A client discovers that her happiest memory—her wedding day—is entirely fabricated. The implant was a gift from her husband, who wanted her to remember their marriage as perfect even though it was troubled. She wants the real memory restored. The real memory is of a fight, tears, and a moment of genuine connection that was messier but more meaningful. Restoration requires erasing the fabrication, but the fabrication has been part of her identity for 20 years. Removing it is a kind of death. She asks you what she should do. You don't know. Your own memories are suspect. Your certification training included a module on "client empathy" that you now suspect was an implant—you remember learning it, but you don't remember the learning. Your earliest memory, of your mother reading to you, has a timestamp that predates your birth. You're teaching authenticity while questioning your own. A student asks if you're okay. You don't know how to answer without lying. You don't know if you know how to lie anymore. The workshop continues. The memories wait.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Memory Preservation Educator";
    state.jobCategory = "Education";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Education listings ]", goto: "careers/cat__education" },
  ],
};
