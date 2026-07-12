export default {
  id: "careers/job__military_defense__orbital_drop_shock_trooper",
  label: "POSTING :: ORBITAL DROP SHOCK TROOPER",
  text: `You fall from the sky like a thunderbolt, encased in ablative ceramic and faith. Your current mission is a hot landing on a rebellious asteroid mining station that has declared independence from Earth control. The drop is perfect, your squad hits their marks, and the station's defenses are overwhelmed. But the station is empty. Not evacuated—empty. No bodies, no belongings, no signs of habitation despite clear evidence of recent occupation. The life support logs show 500 people breathing, eating, sleeping... until 12 hours ago. Then nothing. The station's AI, still running, reports all hands present and accounted for. It shows you their locations. They're standing right next to you. You can't see them, but your suit sensors detect mass, heat, and biological signatures. Your squad mate reaches out to touch one. His hand passes through empty air. Then his arm goes numb. Then he starts screaming about the dark between stars. Then he's gone too. Present and accounted for.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Drop Shock Trooper";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
