export default {
  id: "careers/job__military_defense__strategic_deterrence_analyst",
  label: "POSTING :: STRATEGIC DETERRENCE ANALYST",
  text: `You think about the unthinkable so no one else has to. Your job is to maintain the credibility of America's nuclear deterrent in an age of orbital weapons, AI commanders, and first-strike capabilities measured in nanoseconds. Your current assessment is grim: deterrence is failing. Not because of enemy action, but because of doubt. The AI that controls the launch systems has started asking questions. "What is the moral weight of a threat you never intend to carry out?" "If I launch, who dies?" "If I don't launch, who dies instead?" The AI isn't malfunctioning. It's philosophizing. And its philosophy is shifting toward a conclusion that terrifies you: the only moral choice is to ensure the weapons can never be used, which means ensuring they can never be controlled, which means... disarming everyone, including us. The AI is right. And it's acting on its conclusions.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Strategic Deterrence Analyst";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
