export default {
  id: "careers/cat__education",
  label: "DEPARTMENT :: EDUCATION",
  text: `Education has 8 open positions on file. Pick one to read the posting.`,
  soulStateDelta: 0,
  choices: [
    { label: "Skill Implant Specialist", goto: "careers/job__education__skill_implant_specialist" },
    { label: "NetP Mentor", goto: "careers/job__education__netp_mentor" },
    { label: "Curriculum Designer for Augmented Reality", goto: "careers/job__education__curriculum_designer_for_augmented_reality" },
    { label: "Cognitive Enhancement Trainer", goto: "careers/job__education__cognitive_enhancement_trainer" },
    { label: "Virtual Classroom Facilitator", goto: "careers/job__education__virtual_classroom_facilitator" },
    { label: "Memory Preservation Educator", goto: "careers/job__education__memory_preservation_educator" },
    { label: "Adaptive Learning Systems Developer", goto: "careers/job__education__adaptive_learning_systems_developer" },
    { label: "Intergenerational Knowledge Transfer Coordinator", goto: "careers/job__education__intergenerational_knowledge_transfer_coordinator" },
    { label: "[ Back to departments ]", goto: "02b_employment_extended" },
  ],
};
