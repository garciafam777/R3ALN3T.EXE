export default {
  id: "careers/job__science_research__paleontologist",
  label: "POSTING :: PALEONTOLOGIST",
  text: `You read the bones of the Earth. Your current dig in the Gobi Desert has uncovered something that shouldn't exist: a fossilized city. Not human—older than any known civilization, built by beings with three legs and radial symmetry. The city was buried in a single day, 65 million years ago, by the same asteroid impact that killed the dinosaurs. But the beings didn't die in the impact. They died before it. The fossils show signs of war—weapon injuries, defensive structures, mass graves. They were fighting something. In the deepest layer, you find a single human skeleton, wearing a wristwatch that displays a date: three days from now.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Paleontologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
