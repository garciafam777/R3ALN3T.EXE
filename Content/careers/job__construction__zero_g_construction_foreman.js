export default {
  id: "careers/job__construction__zero_g_construction_foreman",
  label: "POSTING :: ZERO-G CONSTRUCTION FOREMAN",
  text: `You build in the absence of everything that makes building possible—gravity, atmosphere, and the comfort of solid ground. Your current project is "The Lattice"—an orbital manufacturing facility that assembles spacecraft from raw materials mined from asteroids. The Lattice is crewed by 500 workers, all in zero-g, all dependent on your leadership and their own ingenuity. The project is behind schedule. Not because of technical problems, but because the workers are... distracted. They report seeing figures outside the viewports—human-shaped, but moving wrong, as if they're not affected by the lack of gravity. The figures don't appear on cameras, but they show up in the workers' neural recordings. They're getting closer. Yesterday, a worker swore one was inside the station, walking through a bulkhead like it wasn't there. Your safety protocols demand an evacuation. Your contract demands completion. The worker who saw the figure has stopped reporting for duty. You found him in an unfinished section, floating, smiling, and completely unresponsive. His neural log shows he spent the last 6 hours in a conversation with someone who wasn't there. The conversation was about you. The figure told him you'd be joining them soon.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Zero-G Construction Foreman";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
