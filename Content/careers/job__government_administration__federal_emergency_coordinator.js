export default {
  id: "careers/job__government_administration__federal_emergency_coordinator",
  label: "POSTING :: FEDERAL EMERGENCY COORDINATOR",
  text: `When the Cascadia Subduction Zone finally ruptures or a solar flare fries the Eastern Seaboard's power grid, you are the one who decides which cities get rescued and which get written off. You command a fleet of automated relief drones, mobile hospitals, and emergency construction mechs. But resources are finite, and every "save" means a "sacrifice" somewhere else. A mysterious benefactor offers you unlimited private funding—if you prioritize their assets over civilian populations.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Federal Emergency Coordinator";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
