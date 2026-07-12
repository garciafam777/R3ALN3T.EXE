export default {
  id: "careers/job__medical_biosystem__exobiomedical_researcher",
  label: "POSTING :: EXOBIOMEDICAL RESEARCHER",
  text: `You study the biology of alien life. Your current specimen is from Europa—a microbe that survived in the subsurface ocean, brought back by the _Prometheus_ mission. It's alive. It metabolizes. It reproduces. And it's... helpful. When introduced to human tissue, it accelerates healing, fights infection, and seems to enhance cellular function. The military wants to weaponize it. The medical community wants to study it. But the microbe has preferences. It thrives in some patients and dies in others. The pattern isn't genetic, environmental, or behavioral. It's... moral. The microbe grows in people who are kind, cooperative, and altruistic. It dies in the selfish, the cruel, the violent. You're not studying an organism. You're studying a judge.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Exobiomedical Researcher";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
