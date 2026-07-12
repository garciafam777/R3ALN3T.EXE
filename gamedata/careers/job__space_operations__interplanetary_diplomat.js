export default {
  id: "careers/job__space_operations__interplanetary_diplomat",
  label: "POSTING :: INTERPLANETARY DIPLOMAT",
  text: `You negotiate between worlds that have never met face-to-face, where a conversation spans years and a misunderstanding can mean war across the void. Your current negotiation is between Earth and the "Free Martians"—a breakaway colony that declared independence after Earth tried to impose new taxes on helium-3 extraction. The Martians aren't just political separatists. They're becoming something else. Their culture, their biology, their very consciousness is diverging from Earth's. They communicate in ways that don't translate well across the light-speed delay. They make decisions based on values that seem alien. They want recognition not just as a nation but as a distinct form of humanity. Your job is to find common ground, to prevent war, to keep the solar system united. But the Martians have a proposal that changes everything: they want to reclassify the relationship. Not colony and motherland. Not even nation and nation. They want "symbiotic partnership"—a recognition that Earth and Mars are becoming different species, different minds, different ways of being, and that the health of both depends on exchange, not domination. They want to trade technology for culture, resources for wisdom, and independence for alliance. The Earth government wants submission. The Martians want evolution. You're the only one who has spent significant time on both worlds, who understands both perspectives, who might be able to bridge the gap. But bridging gaps requires standing in the middle, and the middle is a dangerous place. Both sides suspect your loyalty. Both sides need your insight. Both sides are preparing for conflict if diplomacy fails. Your next message to Earth will determine the future of the species. Your next message to Mars will determine if there's a future at all. The comms delay is 4 minutes each way. You have 8 minutes to compose a message that prevents war and enables peace. The fate of two worlds is in your hands. And your hands are shaking.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Interplanetary Diplomat";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
