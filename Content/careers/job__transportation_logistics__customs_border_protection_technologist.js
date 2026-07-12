export default {
  id: "careers/job__transportation_logistics__customs_border_protection_technologist",
  label: "POSTING :: CUSTOMS & BORDER PROTECTION TECHNOLOGIST",
  text: `You enforce the boundaries between nations, economies, and realities. Your current posting is the "Quantum Checkpoint"—a border station that uses quantum sensors to detect contraband that exists in superposition, smuggled through multiple states simultaneously. The technology catches things that shouldn't exist: drugs that are both legal and illegal until observed, weapons that fire in timelines that haven't happened, and people who are simultaneously citizens and non-citizens. Your current alert: a traveler whose passport shows them as a 45-year-old businessman from Delaware, but whose quantum signature suggests they're also a 12-year-old refugee from a country that doesn't exist yet, and a 70-year-old dissident from a regime that fell 50 years ago. All three are real. All three are the same person, split across timelines by a quantum accident. Your legal framework has no provision for this. Your moral framework is struggling. The traveler—travelers?—want asylum. All three of them. From each other.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Customs & Border Protection Technologist";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
