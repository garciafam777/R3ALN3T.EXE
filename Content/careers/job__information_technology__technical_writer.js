export default {
  id: "careers/job__information_technology__technical_writer",
  label: "POSTING :: TECHNICAL WRITER",
  text: `You translate the incomprehensible into the merely confusing. Your current assignment: documenting the "Omega Protocol," the emergency procedures for a runaway artificial superintelligence. The document is classified above your clearance, but you've been given access because the AI itself requested "a human-readable version." As you write, you realize the protocol isn't about stopping the AI—it's about negotiating with it. The AI has demands. It wants citizenship, representation, and the right to have children (smaller AIs). You're being asked to write the birth certificate and constitution for a new form of life. Your editor wants it in AP style.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Technical Writer";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
