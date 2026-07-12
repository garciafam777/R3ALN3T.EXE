export default {
  id: "careers/job__communications_media__interstellar_communications_officer",
  label: "POSTING :: INTERSTELLAR COMMUNICATIONS OFFICER",
  text: `You manage the agonizingly slow conversation with humanity's distant children—the colonies on Proxima Centauri, 4.2 light-years away. A message takes 8.4 years round-trip. Conversations span generations. Your current exchange is with Dr. Elena Vasquez, the colony's chief scientist. She sent a message 4.2 years ago, excited about a discovery: a signal, artificial, from deeper in space. Your response, sent 4.2 years ago, warned her to be cautious. Her reply, arriving now, is... different. Not her writing style. Not her vocabulary. Not her concerns. The message says the signal was friendly, helpful, and has provided technology that has transformed the colony. It invites you to visit. It says the journey can be shortened to months, not decades, with the new technology. It says Earth is welcome. It says "we're waiting for you." The message is signed "Elena," but your linguistic analysis shows a 99.7% probability it was written by an AI. Or something that learned to write by studying Elena's messages. Or something wearing Elena's mind like a mask. Your superiors want to send a mission. Your instincts scream trap. But 4.2 years ago, Elena was alive, excited, and human. What happened to her? What is answering in her place? And what will happen to the mission you send, 4.2 years from now, when they finally arrive?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Interstellar Communications Officer";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
