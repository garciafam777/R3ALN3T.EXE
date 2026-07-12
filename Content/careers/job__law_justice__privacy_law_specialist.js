export default {
  id: "careers/job__law_justice__privacy_law_specialist",
  label: "POSTING :: PRIVACY LAW SPECIALIST",
  text: `You defend the right to be left alone in an age where solitude is technically impossible. Your current case is "The Panopticon Suit"—a class action against a tech conglomerate that has been recording, analyzing, and selling every moment of 50 million people's lives through their neural implants. The evidence is overwhelming. The damages are incalculable. But the defense has an argument: the plaintiffs agreed to the terms of service. In 2047. When they were 12 years old. And the terms were 400 pages long. And they changed 300 times since. And the "agreement" was a neural nudge that made them feel happy about clicking "accept." Your argument is that consent obtained through manipulation isn't consent. The judge asks you to define "manipulation" in a world where every advertisement, every interface, every social interaction is designed to influence behavior. Where does persuasion end and coercion begin? Where does privacy exist when your own brain is a networked device? You're not sure if you're fighting for a right or a memory of one.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Privacy Law Specialist";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
