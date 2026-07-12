export default {
  id: "careers/job__military_defense__exo_armor_pilot",
  label: "POSTING :: EXO-ARMOR PILOT",
  text: `You wear a machine that makes you more than human. Your current suit, "Titan-7," is a 3-meter bipedal war machine with strength enough to lift tanks, armor enough to survive orbital re-entry, and weapons enough to level city blocks. You are deployed to "pacify" a riot in the Detroit Autonomous Zone, where humans augmented with illegal neural interfaces have achieved a form of collective consciousness. The riot isn't violent—it's a sit-in, a refusal to participate in an economy that treats them as obsolete. Your orders are to disperse them. Your suit's AI suggests negotiation. The rioters aren't afraid of you. They're pitying you. "You're still alone in there," their spokesman says, tapping your armor. "We can hear the silence." Your suit's sensors detect no weapons, no threats. But your heart rate is spiking, your cortisol is flooding, and for the first time in your military career, you feel... small. The suit can't protect you from that.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Exo-Armor Pilot";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
