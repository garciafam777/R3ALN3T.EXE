export default {
  id: "careers/job__engineering__structural_engineer",
  label: "POSTING :: STRUCTURAL ENGINEER",
  text: `You ensure that buildings stand and bridges don't fall. Your current crisis is "The Leaning Tower of Dubai"—a kilometer-high arcology that has developed a 2-degree tilt. The structure is sound; the tilt is impossible given the foundation data. Your investigation reveals the building is responding to something beneath it—a massive void, perfectly spherical, 2 kilometers in diameter. The void wasn't there when the foundation was poured. It's growing. The building isn't falling; it's pointing. At something in the sky that your telescopes can't see, but your tilt sensors can track. The tower leans a little more every day. So do the people who live in it. They don't notice. They just walk at a slight angle, like the world has shifted and only they know.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Structural Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
