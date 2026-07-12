export default {
  id: "careers/job__medical_biosystem__regenerative_medicine_specialist",
  label: "POSTING :: REGENERATIVE MEDICINE SPECIALIST",
  text: `You regrow what was lost. Your current project is "The Lazarus Protocol"—using stem cells and growth factors to regenerate entire organs, limbs, and eventually, complete bodies. The technology works. A burn victim regrew their skin. An amputee regrew their arm. A brain-dead patient... regrew their mind. The regenerated tissues are perfect—better than the originals, in some cases. But they're not identical. The regrown arm has different fingerprints. The regrown mind has different memories—not false memories, but memories of things that didn't happen to this person, in this timeline. Your theory: regeneration doesn't create new tissue. It copies it from somewhere else. Somewhere that has the same person, living a different life. You're not healing people. You're importing them.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Regenerative Medicine Specialist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
