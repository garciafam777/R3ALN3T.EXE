export default {
  id: "careers/job__military_defense__counter_insurgency_specialist",
  label: "POSTING :: COUNTER-INSURGENCY SPECIALIST",
  text: `You fight wars that don't officially exist. Your current assignment is hunting "The Architects"—a decentralized resistance movement that operates across Earth, orbit, and the Martian colonies. They have no leaders, no headquarters, no uniform ideology. They simply... build. Unauthorized structures in restricted zones, alternative infrastructure that bypasses corporate control, and "liberation gardens" that grow food outside the agricultural cartels. Your job is to find them, understand them, and dismantle them. But the more you study, the more you realize: the Architects aren't a movement. They're a method. A distributed, emergent behavior that arises whenever human creativity is suppressed. You can't arrest an idea. You can't bomb a philosophy. And the more you fight them, the more you sound like them. Your last report was flagged for "sympathetic language." Your handler wants to know whose side you're on. You're starting to wonder if sides are the problem.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Counter-Insurgency Specialist";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
