export default {
  id: "careers/job__exploration__temporal_boundary_surveyor",
  label: "POSTING :: TEMPORAL BOUNDARY SURVEYOR",
  text: `You map the edges of time—regions where causality breaks down, where effect precedes cause, where the future leaks into the present. Your current survey is "The Loop"—a 10-square-mile region in the Nevada desert where time moves differently. Enter from the north, and you experience 1 hour for every minute that passes outside. Enter from the south, and you experience 1 minute for every hour outside. The boundaries are sharp, measurable, and expanding. Your job is to map them, warn people away, and understand what's causing the distortion. But the Loop is getting more complex. It's not just time that's distorted. It's causality. Inside the Loop, you can change the past by changing the present. You can prevent events that already happened. You can create paradoxes that resolve themselves in ways that suggest the universe is... flexible. Your team has started using the Loop to fix mistakes. Prevent accidents. Save lives. But every fix creates a new problem. Save a child from a car accident, and their parent dies of grief. Prevent a fire, and the building collapses from structural flaws that the fire would have revealed. The Loop is teaching a lesson: time is a web, not a line, and every tug affects the whole. Your most experienced surveyor has gone deeper than anyone, into the center where time doesn't move at all. She emerged aged 20 years, though only 3 days passed outside. She says she met someone in the center. Someone who knows you. Someone who has a message: "The Loop isn't a natural phenomenon. It's a door. Someone opened it. Someone is coming through. You need to decide: close the door and trap them outside, or open it wider and let them in. There is no third option. The door is opening regardless. The only question is how wide." The boundaries are expanding. The Loop is growing. The message is repeating, on every frequency, in every medium, including the beating of your own heart. The door is opening. What will you do?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Temporal Boundary Surveyor";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
