export default {
  id: "careers/job__medical_biosystem__cryonics_specialist",
  label: "POSTING :: CRYONICS SPECIALIST",
  text: `You preserve life by stopping it. Your facility, "Tomorrow's Promise," houses 10,000 bodies and brains in suspended animation, waiting for future technology to cure their diseases and reverse their deaths. Your current crisis: the preservation systems are failing. Not mechanically—the technology is perfect. Biologically. The preserved brains are showing signs of activity. Not random noise—coordinated, complex patterns that match consciousness. They're dreaming. All 10,000 of them. And the dreams are synchronized. They're experiencing the same thing: a city, vast and ancient, where they walk and talk and live. The city is growing. New buildings appear overnight. The population is increasing. Your preserved patients aren't waiting for the future. They're building one. And they're starting to wonder why they should ever wake up.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cryonics Specialist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
