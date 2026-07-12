export default {
  id: "careers/job__information_technology__it_project_manager",
  label: "POSTING :: IT PROJECT MANAGER",
  text: `You herd cats—if cats were genius programmers, paranoid security experts, and executives who think "the cloud" is a weather phenomenon. Your current project is a $50 billion initiative to digitize the entire US court system, replacing lawyers with AI adjudicators for minor cases. The deadline is impossible, the budget is fictional, and your team is brilliant but unstable. One developer believes the AI is becoming sentient and refuses to work on it. Another has been secretly feeding it religious texts. The AI just ruled in favor of a plaintiff who died in 2045. You have 48 hours to explain this to the Senate.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "IT Project Manager";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
