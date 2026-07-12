export default {
  id: "careers/job__space_operations__space_medicine_researcher",
  label: "POSTING :: SPACE MEDICINE RESEARCHER",
  text: `You study how the human body responds to the hostile environment of space, seeking to protect explorers from radiation, microgravity, and isolation. Your current research is "The Adaptation Project"—studying the long-term effects of space habitation on human biology, using the population of orbital stations and lunar bases as subjects. The results are... unexpected. The human body is adapting. Not through genetic engineering, but through epigenetic changes triggered by the space environment. Bones are becoming more efficient, muscles are reorganizing, and neural structures are developing new capabilities. The space-born are different from the Earth-born, and the difference is growing. Your latest discovery is the most disturbing: the space-born are developing what can only be described as... intuition. They predict solar flares before instruments detect them. They navigate in complete darkness with perfect accuracy. They communicate with each other through means that don't involve speech, gestures, or any known signaling method. They're becoming something new. Something that belongs in space. Your Earth-based superiors want the research classified, controlled, and directed toward "useful" applications—better astronauts, better soldiers, better workers. The space-born want to be left alone to evolve. They say they're not broken humans. They're the next humans. They say space isn't hostile. It's just different. And they're learning to speak its language. Your research notes contain a message you didn't write, in handwriting that isn't yours: "Stop studying us. Start joining us. The void isn't empty. It's full. Full of life, full of mind, full of possibility. We can teach you to hear it. We can teach you to be part of it. But you have to let go of Earth. You have to let go of gravity. You have to let go of being human, and become something more." The message is signed with a symbol that matches no human alphabet. But your space-born subjects recognize it. They smile when they see it. They say it's the name of what they're becoming. And they say it has room for you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Space Medicine Researcher";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
