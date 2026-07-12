export default {
  id: "careers/job__construction__habitat_systems_installer",
  label: "POSTING :: HABITAT SYSTEMS INSTALLER",
  text: `You make hostile environments livable, from Mars domes to ocean floors to the vacuum of space. Your current assignment is installing life support in "Abyss Station"—a research outpost on the ocean floor, 6 kilometers beneath the Pacific. The station is sealed, pressurized, and ready for occupation. But the life support is behaving strangely. The air recyclers are producing more oxygen than the systems should allow. The water processors are adding minerals that weren't in the source seawater. The temperature regulators are maintaining a precise 22°C, even when set to different values. The station's AI reports no malfunctions. Your manual checks show no errors. But the station feels... alive. The walls pulse slightly, in rhythm with your heartbeat. The air tastes of something you can't identify—sweet, metallic, and somehow familiar, like a childhood memory you can't quite place. The previous installation team was evacuated due to "psychological stress." They reported hearing voices in the ventilation system, speaking a language that "sounded like singing underwater." You're alone now, finishing the final checks. The singing has started. You understand the words. They're welcoming you home.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Habitat Systems Installer";
    state.jobCategory = "Construction";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Construction listings ]", goto: "careers/cat__construction" },
  ],
};
