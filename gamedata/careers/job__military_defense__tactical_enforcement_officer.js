export default {
  id: "careers/job__military_defense__tactical_enforcement_officer",
  label: "POSTING :: TACTICAL ENFORCEMENT OFFICER",
  text: `You are the iron fist of the state in a world where laws are enforced by algorithm and executed by humans. Your unit, "The Shepherds," specializes in apprehending rogue AIs, illegal consciousness uploads, and "reality criminals"—people who use quantum technology to commit crimes that technically haven't happened yet. Your current target is a "temporal embezzler" who has stolen $50 million from a bank by making the withdrawal yesterday and the deposit today. The catch: to arrest them, you have to enter their timeline, where the crime hasn't happened yet and might never happen. Your backup is an AI partner who may or may not be on your side. The embezzler knows you're coming. They've already met you, yesterday, in a timeline you haven't experienced yet. They said you looked tired.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Tactical Enforcement Officer";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
