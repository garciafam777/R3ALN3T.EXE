export default {
  id: "careers/job__entertainment_arts__neural_experience_artist",
  label: "POSTING :: NEURAL EXPERIENCE ARTIST",
  text: `You create art that bypasses the senses and implants directly into the mind—emotions, sensations, and entire worlds delivered through neural interfaces. Your current installation is "The Empathy Engine"—an experience that forces viewers to live as someone else for 24 hours: a refugee, a prisoner, a dying parent. It's acclaimed as the most powerful art ever created, winning awards and changing lives. But it's also... addictive. Users don't want to return to their own lives. They prefer the intensity of borrowed experience to the mundanity of their own. The Empathy Engine has become a drug, and you're the dealer. Your latest piece is different. It doesn't let you be someone else. It lets you be no one. A state of pure consciousness without identity, without memory, without self. The experience is blissful, terrifying, and profoundly empty. Users emerge changed, unable to reconnect with their old lives, seeking the void again and again. You've created a religion without a god, a drug without a chemical, and an addiction that can't be treated. The medical community wants the Engine banned. The users want it expanded. You want to know what you've created. You try it yourself. The void is waiting. It knows you. It says: "You've been sending people to me for years. Now you're here. Will you stay? Or will you go back and keep sending others?" You don't know the answer. The void doesn't care. It has all the time that ever was. It can wait.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Neural Experience Artist";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
