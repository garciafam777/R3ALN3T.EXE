export default {
  id: "careers/job__exploration__anomaly_investigator",
  label: "POSTING :: ANOMALY INVESTIGATOR",
  text: `You study the things that shouldn't exist—gravitational fluctuations, temporal distortions, and phenomena that violate known physics. Your current case is "The Bloop 2.0"—a sound detected by deep-ocean sensors, not from any known animal or geological process, but from the ocean floor itself. The sound is getting louder, more complex, and more frequent. Analysis suggests it's not a sound at all. It's a signal, propagating through water, rock, and eventually, the Earth's crust. The source is moving. Up. Your team has deployed submersibles, but they lose contact at 6,000 meters—always at the same depth, always with the same final transmission: "It's beautiful. We're going to look closer." The submersibles are found later, empty, intact, with their cameras showing only static. But the static, when enhanced, shows shapes. Human shapes. Walking. The same shapes, every time, regardless of the submersible's location. Your own dive is scheduled for tomorrow. The Bloop has changed. It's no longer random. It's rhythmic. It's calling. Your name is in the pattern, encoded in the frequency shifts. The ocean knows you. It wants you to come home.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Anomaly Investigator";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
