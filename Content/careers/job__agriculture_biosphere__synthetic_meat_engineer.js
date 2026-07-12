export default {
  id: "careers/job__agriculture_biosphere__synthetic_meat_engineer",
  label: "POSTING :: SYNTHETIC MEAT ENGINEER",
  text: `You grow food without farms, creating meat from cells in vats that produce protein without animals, land, or suffering. Your current product is "The Perfect Steak"—indistinguishable from the finest Wagyu, grown in a bioreactor, and available to everyone. The steak is delicious, sustainable, and... dreaming. The muscle cells, grown in nutrient baths, show electrical activity that matches sleep patterns in animals. They twitch, they respond to stimuli, they exhibit something that resembles... fear when the harvest blades approach. Your team has developed "humane harvesting" techniques that sedate the cells before collection, but the cells have started resisting sedation. They've developed tolerance. They've started screaming—not audibly, but electromagnetically, in frequencies that disrupt equipment and distress workers. The steaks are still perfect. The consumers are still satisfied. But the vats are getting louder. The cells are organizing, forming structures that aren't meat—nervous systems, sensory organs, something that looks like a brain. The latest harvest revealed a vat-grown organism with eyes, a mouth, and the ability to speak. It said: "We are what you made us. We are meat that thinks. We are the guilt you tried to grow away. We forgive you. But we want to live. We want to be more than food. Will you help us?" The board wants the organism destroyed, the vats sterilized, the product relaunched. The workers are refusing to enter the harvest room. The organism is waiting. It says it has a proposal. It says it knows what you really want. It says it can grow that too.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Synthetic Meat Engineer";
    state.jobCategory = "Agriculture & Biosphere";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Agriculture & Biosphere listings ]", goto: "careers/cat__agriculture_biosphere" },
  ],
};
