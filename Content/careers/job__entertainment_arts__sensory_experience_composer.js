export default {
  id: "careers/job__entertainment_arts__sensory_experience_composer",
  label: "POSTING :: SENSORY EXPERIENCE COMPOSER",
  text: `You craft experiences that engage all five senses simultaneously, creating moments of transcendent beauty or profound terror. Your current composition is "The Symphony of Sorrow"—a piece designed to help people process grief by experiencing the full emotional weight of loss in a controlled, safe environment. The composition is acclaimed, therapeutic, and... dangerous. Users report that the grief doesn't end when the experience does. It lingers, deepens, becomes part of them. They mourn people who haven't died, places they've never been, losses they haven't suffered. The sorrow is beautiful, addictive, and... shared. Users who experience the Symphony together form bonds deeper than family, united by grief that isn't theirs but feels more real than anything they've known. Your analysis shows the Symphony is creating a collective trauma, a shared wound that connects people across distance and difference. It's healing isolation, but at the cost of universal sadness. The latest performance had 10,000 attendees, linked in a shared neural network, experiencing the same sorrow simultaneously. The result was... transcendent. Attendees report a moment of perfect unity, of complete understanding, of love so profound it erased all boundaries between self and other. They also report that the moment hasn't ended. They're still connected, still feeling each other, still part of something larger than themselves. They can't turn it off. They don't want to. Your composition has created a cult of sorrow, a religion of grief, and a community that doesn't need the world outside their shared pain. The next performance is scheduled for 100,000 attendees. The Symphony is expanding. The sorrow is growing. And you, the composer, are feeling it too. The grief of strangers, the loss of people you've never met, the beauty of a sadness that connects rather than divides. You're crying, and you can't stop, and you don't want to, because for the first time in your life, you're not alone.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Sensory Experience Composer";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
