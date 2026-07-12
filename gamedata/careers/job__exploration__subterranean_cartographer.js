export default {
  id: "careers/job__exploration__subterranean_cartographer",
  label: "POSTING :: SUBTERRANEAN CARTOGRAPHER",
  text: `You map the world beneath our feet, the vast cave systems, magma chambers, and hollow spaces that make up Earth's hidden geography. Your current survey is of "The Deep Road"—a tunnel system beneath the Appalachian Mountains that doesn't match any known geological formation. The tunnels are smooth, circular, and precisely 3 meters in diameter. They extend for hundreds of miles, descending at a steady angle that would eventually reach the mantle. Your team has mapped 200 miles. The tunnels are identical, featureless, and clean—no debris, no water, no life. Until yesterday. Yesterday, you found a chamber. Spherical, 100 meters across, with walls covered in... writing. Not carved, not painted—grown, like lichen, forming symbols that shift slowly, like they're alive. The symbols match no known language, but your neural implant can almost translate them. They speak of a journey. Of a people who went down, not up. Of a world beneath the world, where the rules are different, where the dark is warm, where time moves slowly and thought moves quickly. They left the tunnels for others to follow. They left them for you. Your team wants to turn back. Your scientific curiosity wants to continue. The symbols are getting clearer. They say: "We knew you would come. We left the road for you. The door is open. The light is waiting. But be careful. The light is not what you think." Your flashlight flickers. The chamber is getting warmer. The symbols are spelling out your name.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Subterranean Cartographer";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
