export default {
  id: "careers/job__medical_biosystem__neural_surgeon",
  label: "POSTING :: NEURAL SURGEON",
  text: `You operate on the seat of consciousness. Your current case is "Patient X"—a victim of a neural implant hack that left their brain partially encrypted. The implant manufacturer says the encryption is unbreakable. You don't believe in unbreakable. You devise a procedure to bypass the implant and access the brain directly, using a technique that's never been tried on a living human. It works. Patient X wakes up, but they're different. They remember things that didn't happen, know things they couldn't know, and speak languages they never learned. They say the encryption wasn't malicious—it was protective. Something was trying to get out of their mind, not in. They want the implant back. They miss the silence.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Neural Surgeon";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
