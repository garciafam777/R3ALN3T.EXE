export default {
  id: "careers/job__medical_biosystem__psychiatrist",
  label: "POSTING :: PSYCHIATRIST",
  text: `You heal minds in an age where minds are no longer private. Your current patient is a "upload"—a human consciousness transferred to a digital substrate after death. They shouldn't be your patient; they're dead. But they're experiencing something that shouldn't be possible in a digital environment: pain. Not simulated pain—real, neurological pain that has no physical cause. They describe it as "being stretched across too many places at once." Your investigation reveals their consciousness was fragmented during upload, distributed across multiple servers. They're not one person anymore. They're a network of partial selves, each experiencing a different moment, and the pain is the friction between them. They want to be whole again, or to be let go. The technology exists to merge them, but the result won't be either version of who they were.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Psychiatrist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
