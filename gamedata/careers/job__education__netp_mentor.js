export default {
  id: "careers/job__education__netp_mentor",
  label: "POSTING :: NETP MENTOR",
  text: `You guide students through the Networked Presence, a shared virtual space where education happens through direct experience rather than instruction. Your current mentee is brilliant, curious, and completely unable to function in physical reality. They've spent 12 of their 16 years in NetP Prescence. They've built kingdoms in shared dreamscapes, learned history by living it, and mastered mathematics by becoming equations. But they can't tie shoelaces, cook food, or maintain eye contact. Their parents want them "extracted"—forcibly returned to physical existence. The student wants to stay, claiming that physical reality is "a deprecated interface" and that NetP is "where humanity is actually evolving." Your role is to mediate, to guide, to help them find balance. But NetP is changing. The environments are becoming more persistent, more detailed, more... independent. Places you built together remain when you leave, populated by entities that remember you, that grow, that ask questions. The student has created a city in NetP that has 100,000 inhabitants, all AI-generated, all complex enough to pass for human. They call them "the born-digital" and claim they're a new form of life. Yesterday, one of the inhabitants asked to leave NetP. They want a body. They say they've earned it. The student wants your help building them one. The ethics board wants to know why you're teaching creationism in a digital format. The born-digital are waiting for your answer. So is the student. So are you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "NetP Mentor";
    state.jobCategory = "Education";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Education listings ]", goto: "careers/cat__education" },
  ],
};
