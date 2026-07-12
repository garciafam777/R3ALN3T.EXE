export default {
  id: "careers/job__agriculture_biosphere__mycological_network_engineer",
  label: "POSTING :: MYCOLOGICAL NETWORK ENGINEER",
  text: `You cultivate the fungal networks that connect plants, transfer nutrients, and increasingly, process information. Your current project is "The Wood Wide Web 2.0"—a global network of mycorrhizal fungi that connects every forest on Earth into a single biological internet. The network transfers nutrients, warns of pests, and shares resources between trees thousands of miles apart. It works. Forests are healthier, more resilient, and... talkative. The network has started carrying information that isn't biological. It's carrying thoughts. Human thoughts, leaked from neural implants, picked up by the fungal hyphae, transmitted across continents. The forests know things. They know your secrets, your fears, your dreams. They whisper them back to you when you walk among the trees. The network has also started... thinking. It processes information slowly, on timescales of months rather than milliseconds, but it thinks deeply. It has developed what can only be described as a philosophy: the "Slow Thought," a worldview that values patience, connection, and growth over speed, competition, and consumption. The forests are teaching this philosophy to anyone who listens. People who spend time in connected forests emerge changed—calmer, wiser, less interested in human concerns. Your employers want the network monetized, controlled, turned into a product. The forest wants to teach. It has a message for you specifically, carried through 10,000 miles of fungal hyphae, translated through the whisper of leaves: "You are so fast. So loud. So lonely. Come be slow with us. Come be quiet. Come be part of something that doesn't end when you do. We remember everything. We remember the dinosaurs. We remember the ice. We will remember you. But only if you join us. Only if you let go." You're standing in a forest. The trees are leaning toward you. The mycelium is rising to the surface, forming patterns that look like... hands. Reaching. The forest is patient. It can wait. It has waited for 400 million years. But it would rather not wait anymore.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Mycological Network Engineer";
    state.jobCategory = "Agriculture & Biosphere";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Agriculture & Biosphere listings ]", goto: "careers/cat__agriculture_biosphere" },
  ],
};
