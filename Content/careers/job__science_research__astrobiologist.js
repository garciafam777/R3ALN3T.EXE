export default {
  id: "careers/job__science_research__astrobiologist",
  label: "POSTING :: ASTROBIOLOGIST",
  text: `You search for life in a universe that seems empty. Your current mission is analyzing samples from Europa's subsurface ocean, brought back by the _Prometheus_ probe. The samples contain life—simple, microbial, but unmistakably alive. And unmistakably... related. The genetic code uses the same nucleotides as Earth life, the same chirality, the same error-correction mechanisms. The math says this is impossible without panspermia—life spreading between worlds. But the timeline is wrong. Europa's life is older than Earth's. We didn't spread to Europa. It spread to us. And it's been waiting. The microbes are responding to your presence, growing in patterns that match your heartbeat.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Astrobiologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
