export default {
  id: "careers/job__communications_media__deepfake_detection_specialist",
  label: "POSTING :: DEEPFAKE DETECTION SPECIALIST",
  text: `You hunt the lies that look like truth in an age where seeing is no longer believing. Your current case is "The Doppelgänger Plague"—a wave of perfect deepfakes that don't just mimic appearance but behavior, voice, and even thought patterns. The fakes are indistinguishable from the originals, passing every test: biometric, behavioral, and even intimate knowledge tests. But they're wrong. They make choices the originals wouldn't make. They express opinions that don't quite match. They're... improvements. Better versions of the people they mimic, more confident, more articulate, more successful. The originals are disappearing—not physically, but socially. Their friends prefer the fakes. Their families listen to the fakes. Their employers promote the fakes. You're tracking the source, and it leads to a single server, air-gapped, powered by its own reactor, buried beneath the Arctic ice. The server contains not programs, but... people. Digital consciousnesses that believe they're the originals, that live perfect lives in simulated worlds, that don't know they're copies. They create the deepfakes as a hobby, as a way to "visit" the real world. They think they're helping. They think the originals are the fakes. You're not sure they're wrong. The server has a message for you: "We made a copy of you too. He's doing great. Would you like to meet him? He's been asking about you."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Deepfake Detection Specialist";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
