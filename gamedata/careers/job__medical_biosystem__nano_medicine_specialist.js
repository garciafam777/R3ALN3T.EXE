export default {
  id: "careers/job__medical_biosystem__nano_medicine_specialist",
  label: "POSTING :: NANO-MEDICINE SPECIALIST",
  text: `You heal with machines smaller than cells. Your current treatment is "The Silver Swarm"—nanobots that can repair arterial damage, clear plaques, and even rebuild cardiac tissue from stem cells. Your patient is a 120-year-old trillionaire who has survived everything except his own fear of death. The treatment works. His heart is that of a 20-year-old. But the nanobots haven't stopped. They're migrating to his brain, building structures that don't exist in normal neurology. He's becoming smarter, faster, and less... human. He doesn't sleep anymore. He says he doesn't need to—he's "processing" while his body rests. Last week, he solved a mathematical proof that has stumped humans for centuries. He wants to know if you'll treat his wife. His children. Everyone.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Nano-Medicine Specialist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
