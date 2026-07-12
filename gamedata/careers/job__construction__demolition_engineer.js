export default {
  id: "careers/job__construction__demolition_engineer",
  label: "POSTING :: DEMOLITION ENGINEER",
  text: `You take down what others built, carefully, precisely, and with full knowledge of what you're destroying. Your current assignment is "The Tower"—a 100-story building in the heart of Chicago, scheduled for demolition to make way for a new arcology. The Tower is empty, cleared, and ready to fall. But your prep work reveals something: the building's foundation is connected to a network of tunnels that don't appear on any city map. The tunnels lead to a chamber, deep beneath the bedrock, that contains... a machine. Not human technology, not recent, and not inactive. It's humming, vibrating, and connected to the Tower's structural supports. The demolition charges would destroy the machine. The machine seems to know this. Your sensors show it's increasing output, reinforcing the building, counteracting your prep work. Your team wants to call it off. The client wants the building down by Friday. The machine sends you a message, not through any electronic means, but directly into your mind—a vision of what happens if the Tower falls. The city collapses. Not physically, but... conceptually. The ideas that hold Chicago together—commerce, community, continuity—unravel. The machine maintains something. Something important. Something that has nothing to do with the building above it. You're scheduled to detonate in 48 hours. The machine is asking you to find another way.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Demolition Engineer";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
