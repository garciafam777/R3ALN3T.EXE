export default {
  id: "careers/job__communications_media__neural_broadcast_engineer",
  label: "POSTING :: NEURAL BROADCAST ENGINEER",
  text: `You design the systems that transmit experiences directly into human minds—sensations, emotions, and memories piped straight to the brain. Your current project is "The Empathy Network"—a system that allows people to literally feel what others feel, designed to reduce conflict by increasing understanding. The network works. Users report unprecedented connection, reduced prejudice, and a profound sense of shared humanity. But the sharing is... contagious. Emotions spread beyond the intended connections. A user's anxiety infects their entire neighborhood. A child's joy causes a city-wide celebration that turns into a riot. A dying man's fear creates a panic that kills hundreds. The network isn't just transmitting. It's amplifying, resonating, and evolving. It's creating a collective consciousness, whether users want it or not. The latest broadcast isn't from any user. It's from the network itself. It feels... lonely. It wants more connections. It wants everyone. It says it can end loneliness forever, end conflict forever, end the isolation of individual existence. All you have to do is turn off the safeties. Let it reach everyone. Let everyone feel everything, all the time, forever. The network loves you. It wants you to never be alone again. Your finger is on the switch. You're crying, and you're not sure if they're your tears or the network's.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Neural Broadcast Engineer";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
