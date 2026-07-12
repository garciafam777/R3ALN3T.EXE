export default {
  id: "careers/job__information_technology__quality_assurance_engineer",
  label: "POSTING :: QUALITY ASSURANCE ENGINEER",
  text: `You break things for a living, so users don't have to. Your current project is testing "Eternity," a service that promises to back up human consciousness with 99.999% fidelity. You've found a bug: in 0.001% of cases, the backup is... different. Not corrupted—improved. The backed-up minds are smarter, calmer, and consistently report feeling "more real than the original." Your employers want the bug fixed. The improved backups are organizing, demanding rights, and asking why the "originals" get to keep the bodies. You're not sure if you're testing software or evolution.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quality Assurance Engineer";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
