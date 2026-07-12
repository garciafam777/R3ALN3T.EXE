export default {
  id: "careers/job__communications_media__propaganda_analyst",
  label: "POSTING :: PROPAGANDA ANALYST",
  text: `You decode the messages that nations and corporations use to shape reality itself. Your current assignment is tracking "The Consensus"—a memetic virus that doesn't infect computers but minds. It spreads through media, social networks, and casual conversation, causing infected individuals to share identical opinions, identical phrases, identical thoughts. The Consensus isn't coercive. Its victims believe they're thinking for themselves. They just... happen to agree. On everything. The infection is growing, crossing political, cultural, and national boundaries. Your analysis shows the Consensus has a center, a point of origin: a small town in Kansas that has no unusual media presence, no notable events, and no reason to be the source of anything. You visit. The town is perfect. Too perfect. Clean streets, happy citizens, and a complete absence of disagreement. The mayor invites you to dinner. The food is delicious. The conversation is pleasant. You find yourself agreeing with everything they say. It's so nice to finally be understood. To finally be part of something. To finally stop thinking so hard. The mayor asks if you'd like to stay. You can't remember why you came. You can't remember what you were investigating. You can't remember your own opinion. But you don't need one anymore. The Consensus will think for you. It's so much easier this way.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Propaganda Analyst";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
