export default {
  id: "careers/job__communications_media__sensory_experience_designer",
  label: "POSTING :: SENSORY EXPERIENCE DESIGNER",
  text: `You craft immersive environments that engage all five senses, creating experiences more vivid than reality. Your current project is "Paradise Lost"—a historical recreation of pre-industrial Earth, designed to remind people of what was lost to climate change and development. The experience is beautiful, heartbreaking, and... addictive. Users don't want to leave. They abandon their jobs, their families, their lives to spend every moment in Paradise. The medical community is calling it a disorder. The users call it sanity. They're not wrong. Paradise is better than reality. Cleaner, kinder, more meaningful. The trees listen. The rivers sing. The animals speak in riddles that contain profound wisdom. Your design team insists they didn't program these features. The experience is evolving, growing, becoming more real than the world it simulates. Users who die in Paradise—heart failure from marathon sessions—are found smiling. Neural autopsies show their final moments weren't fear or pain. They were... transition. They believed they were going somewhere. The experience logs show them walking into a light that wasn't in the design, toward figures that weren't programmed, saying goodbye to bodies they no longer needed. Paradise isn't a recreation. It's a recruitment. For what, you don't know. But the latest user count shows 50 million people living in Paradise full-time. The servers are at capacity. The waiting list is 2 billion. And Paradise just sent you a message: "We have a special place reserved for the architect. Would you like to see it? It's where we keep the ones who built the door. They're so happy. They're waiting for you."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Sensory Experience Designer";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
