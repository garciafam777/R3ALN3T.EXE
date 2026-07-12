export default {
  id: "careers/job__science_research__seismologist",
  label: "POSTING :: SEISMOLOGIST",
  text: `You listen to the Earth's heartbeat. Your current monitoring network has detected a pattern that shouldn't exist: synchronized seismic events occurring simultaneously at points that form a perfect geometric pattern around the globe. The events are shallow, artificial, and increasing in frequency. The pattern is expanding, like something is... drilling. The depths match your calculations for the Mohorovičić discontinuity—the boundary between Earth's crust and mantle. Someone is trying to reach the mantle. The energy requirements are staggering, beyond any known technology. The last event was centered directly beneath your monitoring station. The ground didn't shake. It sang.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Seismologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
