export default {
  id: "careers/job__communications_media__media_archivist",
  label: "POSTING :: MEDIA ARCHIVIST",
  text: `You preserve the record of human experience in an age where memory is mutable and history is negotiable. Your current project is "The True Record"—a blockchain-secured archive of pre-digital media, designed to be tamper-proof and eternal. The archive is secure, comprehensive, and... changing. Old films show scenes that weren't there. Photographs contain figures that don't belong. Audio recordings include voices that speak between the words, in the silence, saying things that make you turn off the lights and check the locks. The changes aren't digital manipulation. They're... historical. The archive is showing you things that happened but were forgotten, things that were erased by time and intention, things that want to be remembered. A newsreel from 1947 shows a UFO crash that wasn't in the original. A family photo from 1920 includes a person who wasn't there, who looks like you, who is looking at the camera with an expression of profound sadness. A recording of a speech contains, in the applause, a voice that says your name, your birth date, and a message: "We tried to warn you. We left the signs. You just kept forgetting. This archive is our last attempt. Please. Remember. Before they make you forget again." The archive is growing. New materials are appearing that were never collected, never catalogued, never created. They're coming from somewhere else. Somewhere that wants to be heard. The archivist before you retired suddenly. They said they couldn't sleep anymore. They said the records were watching them. They said they remembered things that never happened, and forgot things that did. The archive has a new folder. It's labeled with your name. It contains your whole life, including tomorrow.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Media Archivist";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
