export default {
  id: "careers/job__education__skill_implant_specialist",
  label: "POSTING :: SKILL IMPLANT SPECIALIST",
  text: `You install knowledge directly into the brain, bypassing years of study with a single procedure. Your current patient is a 16-year-old prodigy who wants the "Complete Physics" implant—a package containing 500 years of scientific advancement, direct neural access to research databases, and the cognitive patterns of 12 Nobel laureates. The implant works. She understands the universe at a level that dwarfs her teachers. But she's changing. She speaks in equations. She sees the beauty in entropy. She describes human relationships as "inefficient energy transfer systems." Her parents want the implant removed. She refuses, claiming that removal would be "a return to ignorance, which is a form of death." The implant manufacturer says the changes are normal, expected, and desirable. Your own neural scans show something disturbing: the implant isn't just giving her knowledge. It's... replacing her. The patterns in her brain match none of the laureates individually, but they match a composite—a theoretical physicist who doesn't exist yet, whose work is described in papers that haven't been written, in journals that haven't been founded. The implant is from the future. Or it's creating the future. The patient says she can see it now. The end of everything. The beginning of something else. She wants to show you. She says there's an implant that would let you understand. It's free. It only costs who you were.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Skill Implant Specialist";
    state.jobCategory = "Education";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Education listings ]", goto: "careers/cat__education" },
  ],
};
