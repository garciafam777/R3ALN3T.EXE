export default {
  id: "careers/job__education__intergenerational_knowledge_transfer_coordinator",
  label: "POSTING :: INTERGENERATIONAL KNOWLEDGE TRANSFER COORDINATOR",
  text: `You bridge the gap between those who remember the old world and those who were born into the new. Your current project pairs "analog elders"—people over 80 who grew up without neural implants, AR, or AI—with "digital natives" who have never known a world without direct brain-computer interfaces. The goal is mutual understanding, wisdom exchange, and social cohesion. The results are unexpected. The elders aren't teaching the young about the past. They're learning from them about the future. And the young aren't dismissive of the old. They're... hungry. For something the elders have that technology can't replicate. A sense of continuity. Of consequence. Of time passing meaningfully. The pairings are forming something unexpected—families of choice, bonded across generations, sharing minds through limited neural links that the elders find terrifying and addictive. One elder, a 92-year-old former farmer, has become a digital prophet, channeling agricultural wisdom into viral content that shapes food policy. One youth, a 16-year-old coder, has abandoned technology to learn hand-craft from her elder partner, creating physical objects that command prices that dwarf digital art. The program is working too well. The boundaries between generations are dissolving. The elders are becoming young in spirit, the young becoming old in wisdom. Society doesn't know how to handle a population that doesn't age in its assumptions. Your funders want metrics. Your participants want to continue. And something is happening in the neural links—information flowing both ways that neither partner is consciously sharing. Memories, skills, intuitions. The elders are dreaming in code. The youth are dreaming in memories that aren't theirs. The transfer is becoming more than knowledge. It's becoming transformation. Your next pairing is yourself with an elder who shares your birthday, 70 years apart. The link is already forming. You can feel them, waiting. They feel familiar. They feel like... you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Intergenerational Knowledge Transfer Coordinator";
    state.jobCategory = "Education";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Education listings ]", goto: "careers/cat__education" },
  ],
};
