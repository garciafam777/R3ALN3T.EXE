export default {
  id: "careers/job__communications_media__emergency_broadcast_system_operator",
  label: "POSTING :: EMERGENCY BROADCAST SYSTEM OPERATOR",
  text: `You maintain the infrastructure that warns humanity of disaster—the tones that interrupt programming, the messages that save lives. Your current shift is routine, until the system activates itself. No alert, no warning, no trigger. The EBS is broadcasting a message, on every frequency, in every language, including ones that don't exist yet. The message is simple: "Do not look up. Do not look up. Do not look up." It repeats, endlessly, with increasing urgency. Your attempts to shut it down fail. The system isn't malfunctioning. It's protecting. From what, you don't know. But your phone is ringing—every phone is ringing—with calls from numbers that don't exist. The callers are screaming about the sky. About something that's always been there but no one noticed. About shapes between stars that are getting closer. About the moon, which isn't the moon anymore, which never was the moon, which is waking up. You want to look up. Everyone wants to look up. The message says don't. Your training says follow protocol. Your curiosity says look. Your window is right there. The sky is so blue. So empty. So full. The message is getting quieter. The callers have stopped. It's so quiet now. Maybe the message was wrong. Maybe it's safe. Maybe you should just... look.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Emergency Broadcast System Operator";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
