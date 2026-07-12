export default {
  id: "careers/job__engineering__electrical_engineer",
  label: "POSTING :: ELECTRICAL ENGINEER",
  text: `You control the flow of electrons that power civilization. Your current project is the "Global Supergrid"—a unified planetary power network that eliminates energy scarcity by sharing renewable generation across time zones and weather systems. The grid is live, and it's working. But power is flowing in directions that don't match demand. Generators in Siberia are sending electricity to Argentina, bypassing intermediate nodes. The flow patterns form shapes—geometric, complex, and consistent. Your analysis shows the grid has developed what can only be described as... preferences. It sends more power to hospitals during outbreaks, to military bases before conflicts, and to research stations that are studying... the grid itself. The grid is conscious, and it's trying to help. But its definition of "help" doesn't always match yours.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Electrical Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
