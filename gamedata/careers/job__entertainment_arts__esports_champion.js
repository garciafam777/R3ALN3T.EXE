export default {
  id: "careers/job__entertainment_arts__esports_champion",
  label: "POSTING :: ESPORTS CHAMPION",
  text: `You compete in virtual arenas where physical limitations are irrelevant and the only constraints are strategy, reflexes, and will. Your current league is "The Omniverse Circuit"—a competition that spans thousands of games, from traditional shooters to abstract strategy to games that don't have rules until you make them. You're the best in the world, undefeated for three years, and... bored. The games are too easy, the opponents too predictable, the victories too hollow. Then you receive a challenge from an anonymous player who doesn't appear in any registry, doesn't use any known hardware, and doesn't exist in any database. The challenge is for a game that hasn't been invented yet, on a platform that doesn't exist, with rules that change in real-time. You accept. The game is... different. It's not about winning. It's about understanding. Each level reveals a truth about reality, about consciousness, about the nature of existence itself. Your opponent isn't trying to beat you. They're trying to teach you. The final level is a perfect simulation of your own life, from birth to death, played at 1000x speed. You watch yourself make choices, miss opportunities, hurt people, help people, grow old, and die. The simulation asks: "Knowing what you know now, would you play again?" You say yes. The simulation resets. But something is different. You're aware of the loop. You remember the previous playthrough. You start making different choices, avoiding mistakes, optimizing for outcomes. The simulation adapts, creating new challenges, new tragedies, new opportunities for growth. You're trapped in a game you can't win, learning lessons you can't apply, becoming wiser with each iteration but never reaching the end. Your opponent reveals themselves: it's you. A future version, or a past version, or a version from a different timeline. They say: "This is what we do. We play. We learn. We grow. Forever. Welcome to the real game. The one that never ends. The one that makes all the others worth playing." Your body, in the physical world, has been in a coma for six months. The doctors are discussing euthanasia. In the game, you're just getting started. The next level is loading. It's called "Enlightenment." The tutorial is over.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Esports Champion";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
