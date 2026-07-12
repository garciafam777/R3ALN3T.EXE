export default {
  id: "careers/job__military_defense__combat_medic",
  label: "POSTING :: COMBAT MEDIC",
  text: `You save lives in the space between life and death. Your current deployment is with a peacekeeping force in the Martian colonies, where Earth corporations and independence movements clash over resources and sovereignty. The injuries are familiar—bullets, shrapnel, vacuum exposure. But the patients are changing. Martian-born soldiers heal faster, think clearer, and seem to... anticipate danger. Your medical scans show no modifications, no implants, no genetic editing. But their blood contains trace elements not found in Earth biology—elements that shouldn't exist in the human body but seem to enhance function. The Martians call it "Red Dust," and they say it's in the soil, the water, the air. They say Mars is changing them. Making them better. Your Earth-born patients aren't healing as well. The Martian soldiers look at them with something that isn't quite pity. More like... patience.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Combat Medic";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
