export default {
  id: "careers/job__medical_biosystem__reproductive_endocrinologist",
  label: "POSTING :: REPRODUCTIVE ENDOCRINOLOGIST",
  text: `You help create life in an age where biology is optional. Your current patient is a same-sex couple who want a child that is genetically theirs both—possible now through advanced gamete engineering. The procedure works. The child is healthy, beautiful, and genetically perfect. Too perfect. The child's DNA contains optimizations that weren't in the parents' genetic code—enhanced metabolism, resistance to disease, and a neural architecture that processes information 50% faster than baseline humans. The parents didn't request these edits. The lab didn't make them. The changes are consistent with... evolution. Accelerated, directed evolution. The child is changing, growing, learning faster than any human should. At six months, they spoke their first word. It was a complete sentence: "Thank you for making me better."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Reproductive Endocrinologist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
