export default {
  id: "careers/job__medical_biosystem__trauma_surgeon",
  label: "POSTING :: TRAUMA SURGEON",
  text: `You put people back together when the world tears them apart. Your current shift is in "The Pit"—an underground trauma center in Chicago that treats victims of the ongoing gang wars, corporate sabotage, and the occasional orbital debris strike. The injuries are getting stranger. Victims of a new street drug called "Void" show wounds that don't match any known weapon—geometric burns, perfectly circular holes, and in one case, a limb that seemed to have been... rotated 180 degrees while still attached. The victims are conscious, coherent, and uniformly terrified of something they can't describe. Your X-rays show nothing wrong. Your patients know better. They beg you not to let them fall asleep. Something comes for them in their dreams.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Trauma Surgeon";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
