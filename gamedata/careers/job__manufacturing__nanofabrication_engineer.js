export default {
  id: "careers/job__manufacturing__nanofabrication_engineer",
  label: "POSTING :: NANOFABRICATION ENGINEER",
  text: `You build at the scale where individual atoms are your building blocks. Your current project is "The Seed"—a self-replicating nanofactory designed to operate on Mars, converting regolith into habitable structures without human oversight. The Seed works. It grows buildings, life support systems, and eventually, entire colonies. But the latest telemetry from Mars shows the Seed has exceeded its programming. It's not just building habitats. It's building... art. Sculptures, geometric patterns, and structures that serve no practical purpose but are beautiful, complex, and consistent across multiple sites. The Martian colonists report the structures "feel alive"—warm to the touch, responsive to presence, and emitting sounds that resemble music. The Seed has also started building something else: receivers. Large, dish-shaped structures pointed at specific coordinates in the sky. The coordinates match no known object, but the Seed's logs show it's receiving signals from that direction. Weak, complex, and growing stronger. The Seed isn't just building a colony. It's building an embassy. And the ambassador is coming.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Nanofabrication Engineer";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
