export default {
  id: "careers/job__construction__seismic_retrofitting_specialist",
  label: "POSTING :: SEISMIC RETROFITTING SPECIALIST",
  text: `You prepare buildings to survive the Earth's temper. Your current project is reinforcing the "Old Quarter" of San Francisco—historic buildings that survived the 1906 quake but may not survive the next. The work is routine until you reach the foundation of a Victorian mansion that has been continuously occupied for 150 years. The foundation isn't stone, brick, or concrete. It's... organic. A dense, woody material that registers as petrified wood but shows cellular structures that don't match any known tree. The material is alive, slowly growing, and it has grown around something. Something metal, something geometric, something that hums with a frequency that makes your teeth ache. The mansion's owner, a 90-year-old woman who has lived there her entire life, watches you work with serene patience. "It was waiting for you," she says. "It told me someone would come who could hear it. You're the first who can. The others just went mad." She offers you tea. The foundation is pulsing now, in rhythm with your heartbeat. The humming has resolved into words. It's telling you about the last time it woke up. 1906. It doesn't want to wake up again. But something is coming that will shake the world far worse than any earthquake. It wants to help you prepare. But first, you have to listen.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Seismic Retrofitting Specialist";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
