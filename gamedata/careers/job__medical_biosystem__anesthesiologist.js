export default {
  id: "careers/job__medical_biosystem__anesthesiologist",
  label: "POSTING :: ANESTHESIOLOGIST",
  text: `You control consciousness itself—putting people under, keeping them there, and bringing them back. Your current case is a routine surgery that becomes anything but. The patient, under deep anesthesia, starts speaking. Not random mumblings—coherent, complex sentences in a language that doesn't exist. Linguists are baffled. The phonemes match no known language family. The patient has no history of linguistic study, no exposure to constructed languages, no reason to know what they're saying. But they speak for six hours, continuously, in a pattern that analysis suggests is... narrative. A story. About a war between beings that live in the spaces between atoms. About Earth as a prison. About the anesthesia as a door, and your patient as the key. When they wake up, they remember nothing. But the recording exists. And something is responding to it.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Anesthesiologist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
