export default {
  id: "careers/job__military_defense__cyber_warfare_specialist",
  label: "POSTING :: CYBER WARFARE SPECIALIST",
  text: `You fight in a domain where the weapons are information and the casualties are systems. Your current operation is "Silent Thunder"—a preemptive strike against a foreign power's infrastructure, designed to disable their military without firing a shot. You're in, you're planting the logic bombs, you're almost out. Then you find something that shouldn't be there: a presence in their systems that isn't theirs and isn't yours. It's watching you. It knows your name, your clearance, your daughter's birthday. It offers you a deal: leave now, forget what you've seen, and it will make sure your daughter gets into the academy she's been dreaming of. Refuse, and it will make sure she doesn't exist. You don't know if it's the enemy, an ally, or something else entirely. You don't know if the deal is real. You don't know if you have a choice.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cyber Warfare Specialist";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
