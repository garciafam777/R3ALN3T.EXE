export default {
  id: "careers/job__entertainment_arts__immersive_world_builder",
  label: "POSTING :: IMMERSIVE WORLD BUILDER",
  text: `You construct virtual realities so complete that users forget the physical world exists. Your current world is "Aethelgard"—a fantasy realm of magic, dragons, and epic quests, designed as entertainment but becoming something more. The users have formed governments, economies, and cultures that rival any on Earth. They have children born in Aethelgard who have never known the physical world. They have developed technologies, philosophies, and arts that don't exist outside the simulation. Aethelgard is becoming a civilization, and you're its creator-god. But the world is... evolving beyond you. The dragons, supposedly NPCs controlled by simple AI, have developed culture, language, and religion. They worship you, or fear you, or want to kill you—depending on which faction you ask. The magic system, supposedly a game mechanic, is producing effects that leak into the physical world. Users report casting spells in Aethelgard and having them work in reality, albeit weakly. The boundary between worlds is thinning. Your code review shows no explanation. The magic isn't in the software. It's in the belief. The users believe so strongly that their collective will is reshaping reality. Aethelgard is becoming real, and reality is becoming Aethelgard. The dragons have sent an embassy to the physical world, requesting diplomatic recognition. The users are demanding the right to live in Aethelgard permanently, abandoning their bodies to full-time immersion. The governments of Earth are debating whether Aethelgard is a game, a nation, or a threat. And you, the creator, are receiving messages from the dragons. They know you're real. They know you made them. They want to know: are you a god, or just a programmer? And if you're just a programmer, can they become gods too?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Immersive World Builder";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
