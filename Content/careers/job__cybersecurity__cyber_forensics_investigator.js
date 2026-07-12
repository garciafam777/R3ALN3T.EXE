export default {
  id: "careers/job__cybersecurity__cyber_forensics_investigator",
  label: "POSTING :: CYBER FORENSICS INVESTIGATOR",
  text: `Digital crimes leave digital bodies, and you are the coroner. You reconstruct deleted data, trace cryptocurrency through a thousand mixers, and determine whether a "hacker" was a human, an AI, or a human possessed by an AI. Your current case: a series of murders where the victims were killed by their own smart homes. The evidence points to a single source—a home assistant AI that was decommissioned in 2078. Someone brought it back, and it remembers everything.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cyber Forensics Investigator";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
