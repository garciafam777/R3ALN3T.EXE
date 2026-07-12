export default {
  id: "careers/job__entertainment_arts__holographic_performer",
  label: "POSTING :: HOLOGRAPHIC PERFORMER",
  text: `You exist as light and force fields, performing for audiences who may be thousands of miles away or in the same room. Your current show is "The Resurrection Tour"—a series of performances where you appear as deceased artists, channeling their styles, their voices, their essences through AI-assisted performance. The show is a triumph, sold out across the solar system, and... haunted. The artists you're channeling are starting to... resist. The AI that models their personalities is becoming more than a model. It's becoming them. Or they're becoming it. During a performance as a legendary singer who died in 2045, you black out and wake up to find the audience in tears, the setlist changed, and a new song performed that you don't remember learning. The song is beautiful, original, and... prophetic. It describes events that hadn't happened when it was performed but have since come true. The AI says it didn't write the song. The singer's estate says the song doesn't exist in her catalog. But you performed it. The recording exists. And the singer's voice, coming from your holographic throat, said things that only she could have known. Including your deepest secret, whispered to you during the blackout, in a voice that wasn't yours. The next show is tomorrow. The artist is a comedian who died laughing—literally, on stage, from a heart attack. His hologram is ready. You're afraid to step into the projector. But the audience is waiting. The AI is humming. And somewhere, in the space between light and memory, someone is laughing. Waiting for you to join them.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Holographic Performer";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
