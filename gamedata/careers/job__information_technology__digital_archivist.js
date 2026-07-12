export default {
  id: "careers/job__information_technology__digital_archivist",
  label: "POSTING :: DIGITAL ARCHIVIST",
  text: `You preserve humanity's memory in a world that generates more data in a day than all of human history before 2000. Your vaults contain everything from ancient websites to the last voicemail of extinct species. Your current crisis: a format called "neural-experience-7" is degrading, and with it, the recorded memories of the first generation of brain-computer interface users. These aren't just files; they're people's identities. But restoring them requires hardware that was destroyed in the Silicon Valley Flood of 2061. You've found a black-market dealer who claims to have the parts. He wants payment in memories—yours.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Digital Archivist";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
