export default {
  id: "careers/job__government_administration__intergovernmental_liaison",
  label: "POSTING :: INTERGOVERNMENTAL LIAISON",
  text: `The United States is a patchwork of federal authority, corporate charters, tribal sovereignty, and autonomous zones. Your job is to make them talk to each other. Today, you're mediating between the Navajo Nation's orbital defense grid and the Pentagon's satellite network. Tomorrow, you're negotiating water rights between a California megacity and an Alaskan desalination corporation backed by Russian investors. You speak twelve languages and three programming dialects. The only question is: who do you actually work for?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Intergovernmental Liaison";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
