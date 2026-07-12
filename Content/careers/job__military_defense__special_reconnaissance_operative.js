export default {
  id: "careers/job__military_defense__special_reconnaissance_operative",
  label: "POSTING :: SPECIAL RECONNAISSANCE OPERATIVE",
  text: `You are the eyes where no eyes should be. Your current insertion is into "The Quiet Zone"—a 500-square-mile area in the Pacific Northwest where all electronics fail, all radio signals die, and all who enter... change. Your mission is to find out why. You go in alone, with nothing but a compass, a knife, and your training. The forest is wrong. Trees grow in spirals. Animals watch you with human eyes. You find a cabin, occupied by a family that doesn't know they're dead. They've been living here for 50 years, unchanged, unaging, unaware that the world has moved on. They invite you to dinner. The food is real. The conversation is normal. But when you look in the mirror, you see yourself as they see you: a ghost, a story, a warning to others who might come. You've been in the Quiet Zone for three hours. Your extraction team reports you've been missing for three weeks.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Special Reconnaissance Operative";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
