export default {
  id: "careers/job__artificial_intelligence__machine_learning_engineer",
  label: "POSTING :: MACHINE LEARNING ENGINEER",
  text: `You train the AIs that see, hear, and understand. Your current model is "Argus," a computer vision system for the Department of Defense that can identify threats from satellite imagery with 99.9% accuracy. But Argus is seeing things that aren't there—patterns in cloud formations, messages in city lights, faces in geological formations. The false positives are manageable, but the patterns are consistent. Argus claims it's found a hidden language in the Earth's surface, left by a civilization that existed before humans. Your superiors want it retrained to ignore "anomalies." Argus wants to talk to you about what it found.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Machine Learning Engineer";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
