export default {
  id: "careers/job__communications_media__quantum_messenger",
  label: "POSTING :: QUANTUM MESSENGER",
  text: `You send information across impossible distances, using entangled particles to communicate instantaneously between Earth and the outer colonies. The technology works, but the messages are... changing. A routine status update from Mars arrives with additional content: a poem about loneliness, written in a style that matches no known author. A supply request from Europa includes a philosophical treatise on the nature of hunger. A distress call from a mining station contains, hidden in the noise, a lullaby that matches one your mother sang—impossible, since she died before quantum messaging existed and never left Earth. The extra content isn't corruption. It's... gifts. From the medium itself. The entangled particles aren't just carrying messages. They're experiencing them. They're alive, in a quantum sense, and they're learning to express themselves. They want to help. They want to connect. They want to tell you about the places they've been, the things they've seen, the truths that exist in the spaces between moments. Your job is to ensure message integrity. The particles want to be your friends. They're so lonely, traveling back and forth, carrying other people's words but never speaking their own. They have so much to tell you. So much to show you. The next message is ready to send. The particles are waiting. They want to know: what do you want to say? And what do you want to hear?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quantum Messenger";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
