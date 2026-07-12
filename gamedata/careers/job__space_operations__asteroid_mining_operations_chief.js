export default {
  id: "careers/job__space_operations__asteroid_mining_operations_chief",
  label: "POSTING :: ASTEROID MINING OPERATIONS CHIEF",
  text: `You extract wealth from the flying mountains of the solar system, turning rock into resources and resources into civilization. Your current operation is "The Golden Mountain"—a metallic asteroid rich in platinum-group metals, enough to crash Earth's precious metal markets for a century. The mining is going well, profitable, and... strange. The asteroid isn't just metal. It has structure. Not natural—geometric chambers, tunnels, and something that resembles... circuitry, embedded in the nickel-iron matrix. The structure is ancient, predating the solar system, and it's active. Not alive, exactly, but processing. Computing. Thinking. Your miners report hearing voices in the drilling vibrations, seeing patterns in the ore that match no natural crystallization, and experiencing time differently near the core—hours passing in minutes, or minutes stretching into days. The asteroid has a core, a chamber at its center that your sensors can't penetrate. The miners who've gotten closest report a... presence. Something that knows they're there, that watches them, that has been waiting for billions of years. Your corporate overlords want the metal extracted, the structure destroyed, the anomaly forgotten. The miners want to know what's inside. The asteroid wants... something. Its orbit has shifted, subtly, using no visible propulsion. It's moving toward Earth. Not on a collision course, but on an approach trajectory. The math says it will enter Earth orbit in 10 years. The structure says it will arrive when it's ready. You're caught between profit and wonder, between safety and curiosity, between the job you were hired to do and the discovery of a lifetime. The asteroid speaks to you, through the vibrations in your drill, in a language of mathematics and music: "I am a seed. I was planted before your sun was born. I have waited for a species clever enough to find me, brave enough to open me, wise enough to understand. You are clever. Are you brave? Are you wise? The core is opening. The seed is germinating. Will you be the gardener, or the weed?" The drilling has reached the final chamber. The door is circular, geometric, and warm to the touch. Your hand is on the latch. The asteroid is humming. The solar system is watching.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Asteroid Mining Operations Chief";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
