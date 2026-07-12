export default {
  id: "careers/job__exploration__deep_sea_salvage_operator",
  label: "POSTING :: DEEP SEA SALVAGE OPERATOR",
  text: `You recover treasure from the ocean floor—sunken ships, lost cargo, and increasingly, the wreckage of orbital craft that didn't survive re-entry. Your current contract is "The Goliath"—a cargo ship that went down in the Pacific 50 years ago, carrying a classified payload that the government wants recovered. The wreck is at 4,000 meters, accessible by your submersible, and mostly intact. The payload is in a sealed vault. You reach it, open it, and find... children. Not bodies. Living children, in suspension pods, unaged, breathing, dreaming. The pods are labeled with dates 100 years in the future. The children are genetically modified—gills, enhanced eyes, skin that photosynthesizes. They're designed for underwater life. They're designed for now. One wakes as you watch. She looks at you with eyes that see in spectrums you can't imagine. She speaks a language you don't know, but your neural implant translates: "You're early. The world isn't ready for us yet. The water isn't clean enough. The air isn't right. Go back. Tell them to wait. We'll come when it's time. But thank you for waking me. I've been dreaming of you. In the dream, you save us. In the dream, you drown. Which one is true?" The pod reseals. The child sleeps. Your contract specifies recovery of the payload. Your conscience asks what "payload" means. The ocean is pressing against your hull. The children are dreaming. One of them is dreaming of you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Deep Sea Salvage Operator";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
