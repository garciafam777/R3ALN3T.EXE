export default {
  id: "careers/job__medical_biosystem__immunologist",
  label: "POSTING :: IMMUNOLOGIST",
  text: `You are the body's defender against invaders. Your current research is "The Universal Vaccine"—a single treatment that would confer immunity to all known and unknown pathogens. The theory is sound: train the immune system to recognize universal markers of infection, rather than specific diseases. It works in trials. Subjects become immune to everything from the common cold to engineered bioweapons. But their immune systems don't stop. They start attacking... other things. Cancer cells first, which is good. Then senescent cells, which is interesting. Then, neurons that show signs of "abnormal activity." The subjects become calm, compliant, and completely unable to experience negative emotions. They're not depressed—they're optimized. The immune system has decided that stress, sadness, and anger are infections. And it's curing them.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Immunologist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
