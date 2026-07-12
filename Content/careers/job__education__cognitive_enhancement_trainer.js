export default {
  id: "careers/job__education__cognitive_enhancement_trainer",
  label: "POSTING :: COGNITIVE ENHANCEMENT TRAINER",
  text: `You teach people to use their augmented minds—neural implants, nootropics, and biofeedback systems that push human cognition beyond natural limits. Your current client is a corporate executive who wants to process information 10x faster, make decisions in milliseconds, and outthink any competitor. The training works. He's sharper, faster, more successful. But he's also... fragmented. His consciousness seems to exist in multiple states simultaneously. He makes decisions before the information is presented. He answers questions before they're asked. He refers to conversations that haven't happened yet and forgets conversations that just did. His neural implant shows unprecedented activity—multiple parallel processing streams that suggest he's thinking in dimensions that don't map to normal spacetime. He claims he's "seeing around corners," perceiving probability spaces rather than single outcomes. He wants to go further, to push beyond the limits you've set. He offers to pay anything. He says he can see "the shape of things to come" and it's beautiful, terrifying, and inevitable. He says there's a pattern, a design, a curriculum written into the fabric of reality itself. He says you're not just a trainer. You're a guide, placed here to help him reach the next lesson. He says the curriculum has levels, and he's almost ready for the final exam. He wants to know if you'll proctor. He says the exam is pass/fail. He says failing isn't what you think.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cognitive Enhancement Trainer";
    state.jobCategory = "Education";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Education listings ]", goto: "careers/cat__education" },
  ],
};
