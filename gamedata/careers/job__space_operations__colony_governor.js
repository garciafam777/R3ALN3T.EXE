export default {
  id: "careers/job__space_operations__colony_governor",
  label: "POSTING :: COLONY GOVERNOR",
  text: `You rule a world where Earth is a memory and survival is a daily negotiation with physics, biology, and human nature. Your current posting is "New Eden"—the largest Martian colony, 50,000 souls dependent on your decisions for air, water, and hope. The colony is thriving, growing, and... restless. The native-born Martians, "Redbloods," are different from the Earth-born "Blues." They think differently, move differently, dream differently. They want independence, not as a political statement but as a biological imperative. They say Mars is changing them, making them something new, something that can't survive on Earth and shouldn't be governed by it. Your Earth superiors want compliance, taxes, and loyalty. Your Martian subjects want freedom, recognition, and the right to evolve. You're caught between worlds, between species, between what was and what will be. The Redbloods have shown you something: their children, born in Martian gravity, are developing adaptations—denser bones, more efficient oxygen use, and a neural structure that processes information differently. They're not just humans on Mars. They're Martians. A new species. And they know it. The question isn't whether Mars will be independent. It's whether you'll be their first leader or their last colonial administrator. The Redbloods are offering you a choice: govern as a bridge between worlds, or be remembered as the tyrant who tried to stop the inevitable. The Earth is demanding loyalty oaths. The Martians are demanding recognition. Your air recycler is making a sound you've never heard before. It's not malfunctioning. It's... singing. In harmony with the Martian wind. The planet is welcoming its children. It wants to know if you're one of them.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Colony Governor";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
