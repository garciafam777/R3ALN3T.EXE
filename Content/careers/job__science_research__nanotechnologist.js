export default {
  id: "careers/job__science_research__nanotechnologist",
  label: "POSTING :: NANOTECHNOLOGIST",
  text: `You work at the scale of atoms, building machines too small to see but large enough to change everything. Your current project is "The Grey Glove"—a medical nanoswarm that can repair tissue at the cellular level, curing any injury or disease. It works in animal trials. In the first human trial, the patient—a terminally ill billionaire—didn't just heal. He improved. His muscles became denser, his neurons fired faster, his skin developed a subtle iridescence. He calls it "evolution." The nanobots are self-replicating, and they're spreading. Not just through his body, but through his environment. The air in his quarantine room contains measurable nanobot concentrations. They're... exploring.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Nanotechnologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
