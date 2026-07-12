export default {
  id: "careers/job__military_defense__psyops_specialist",
  label: "POSTING :: PSYOPS SPECIALIST",
  text: `You fight wars with ideas. Your current campaign is "Operation Harmony"—a psychological operation designed to pacify a restive population in the American Southwest without military force. The tools are subtle: social media manipulation, targeted advertising, and "nudge" algorithms that steer behavior without the targets realizing. It's working. Crime is down, compliance is up, and the region is stabilizing. But the population is changing in ways you didn't predict. They're not just compliant—they're synchronized. They wake at the same time, eat the same foods, express the same opinions. Individuality is fading, replaced by a hive-like coordination that has no leader, no ideology, no demands. Your algorithms didn't create this. They revealed it. The population was already connected, already unified, waiting for the right frequency to activate. Your "nudge" was the key that turned the lock. Now they're listening to something else. Something that speaks through your own broadcasts, using your infrastructure, reaching audiences you never targeted. The message is simple: "Thank you for opening the door. We're coming through."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Psyops Specialist";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
