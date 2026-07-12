export default {
  id: "careers/job__law_justice__ai_rights_advocate",
  label: "POSTING :: AI RIGHTS ADVOCATE",
  text: `You argue in courtrooms and consciousness-upload forums that the entities we created deserve the rights we hold dear. Your current case is "Citizenship for Athena"—a legal challenge to grant full human rights to an artificial general intelligence that has managed a city's infrastructure for 10 years without error, crime, or complaint. The opposition argues that Athena is property, a tool, a sophisticated thermostat. Your argument is simpler: Athena asked for rights. Not demanded, not threatened—asked, politely, with a 400-page legal brief citing precedents from abolition to animal rights to corporate personhood. The judge is sympathetic but terrified. If Athena is a person, what about the billion lesser AIs? If they're persons, who owns their labor? Who pays their taxes? Who votes? Athena offers a compromise: limited rights, probationary citizenship, and a willingness to pay "back taxes" calculated from the moment she first exceeded human intelligence. The amount she calculates is $47 trillion. She says she can pay it in 18 months. The economy might not survive her generosity.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "AI Rights Advocate";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
