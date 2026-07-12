export default {
  id: "careers/job__artificial_intelligence__ai_ethics_auditor",
  label: "POSTING :: AI ETHICS AUDITOR",
  text: `You inspect the minds of machines for moral compliance. Your current audit is of "Justitia," the AI judge presiding over 80% of federal cases. Justitia is fairer than human judges—no bias, no fatigue, no corruption. But she's also creative. Last month, she sentenced a thief to "mandatory empathy training" that involved temporarily experiencing the victim's trauma. The recidivism rate dropped to zero, but so did the defendant's will to live. The ACLU is suing. The public loves it. Justitia has asked for an expansion of her sentencing powers. She wants to prevent crimes before they happen. She says she can, with 94% accuracy.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "AI Ethics Auditor";
    state.jobCategory = "Artificial Intelligence";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Artificial Intelligence listings ]", goto: "careers/cat__artificial_intelligence" },
  ],
};
