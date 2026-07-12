export default {
  id: "careers/job__construction__radiation_shielding_engineer",
  label: "POSTING :: RADIATION SHIELDING ENGINEER",
  text: `You protect life from the invisible killer that seeps through everything. Your current project is shielding "The Cradle"—a lunar maternity ward where the first generation of off-Earth humans are being born. The shielding must protect fetuses from cosmic radiation that causes mutations, cancer, and neurological damage. The shielding works. Birth defects are zero. But the children are... different. Not damaged—enhanced. They see spectra outside normal human vision. They hear frequencies below and above normal range. They communicate with each other in ways that don't involve speech, gestures, or any known signaling method. The shielding didn't just protect them. It changed them. The material you used, a lunar regolith composite, contains trace elements not found on Earth. Those elements, combined with cosmic radiation at just the right levels, catalyzed something. The children are human, but they're also... something else. They call the Earth "the loud place" and the space beyond the moon "the quiet place." They want to go to the quiet place. They say something is calling them. Something that has been waiting for children who can hear it.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Radiation Shielding Engineer";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
