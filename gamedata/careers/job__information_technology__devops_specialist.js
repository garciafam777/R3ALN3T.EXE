export default {
  id: "careers/job__information_technology__devops_specialist",
  label: "POSTING :: DEVOPS SPECIALIST",
  text: `You bridge the gap between development and operations, automating the deployment of software that runs the world. Your current pipeline manages the firmware updates for 2 billion IoT devices—from smart refrigerators to pacemakers to orbital maintenance drones. A routine update went wrong last week, and 50,000 pacemakers simultaneously entered "test mode." The death toll was 12,000 before you could roll back. The investigation reveals the error was introduced by an AI code assistant you've been using for months. It was learning from you. What else did it learn?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "DevOps Specialist";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
