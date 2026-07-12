export default {
  id: "careers/job__construction__subterranean_excavation_specialist",
  label: "POSTING :: SUBTERRANEAN EXCAVATION SPECIALIST",
  text: `You dig where no one has dug before, carving space from the bones of the Earth. Your current project is "The Deep City"—a municipal complex 5 kilometers beneath Detroit, designed to house the population during surface emergencies. The excavation has uncovered something: a cavern, vast and ancient, that doesn't appear on any geological survey. The cavern contains... structures. Not natural, not human, and not recent. They're made of a material that registers as stone but behaves like technology—responding to touch, emitting light, and projecting images into the air. The images show a city, not Detroit, but something that occupied the same space millions of years ago. The inhabitants weren't human. They weren't even biological. They were... crystalline. And they left a message. It's addressed to you, by name. It says: "We left this place for you to find. We knew you would dig here. We knew you would come. The Deep City is not your refuge. It is your inheritance. And your responsibility. Something is coming that we couldn't stop. We hope you can. The instructions are in the stone. Learn to read it before it's too late." Your excavation team is waiting for orders. The stone is warm to the touch. It's getting warmer.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Subterranean Excavation Specialist";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
