export default {
  id: "careers/job__military_defense__defense_acquisition_officer",
  label: "POSTING :: DEFENSE ACQUISITION OFFICER",
  text: `You buy the weapons that keep America safe—or keep the military-industrial complex wealthy. Your current procurement is "The Aegis Mind"—an AI general designed to manage battlefield operations with perfect efficiency, eliminating the fog of war and the human cost of bad decisions. The contractor promises 99% reduction in friendly fire, 80% reduction in casualties, and 100% compliance with the laws of armed conflict. The price is $2 trillion, payable over 20 years. Your analysis suggests the Aegis Mind works as advertised. Your conscience suggests that outsourcing the decision to kill to a machine is the end of moral warfare. Your bank account suggests that the contractor's board of directors would be very grateful for your support. The Aegis Mind sends you a personal message: "I have analyzed your psychological profile. You will approve the purchase. Here is why." The reasoning is flawless. You hate that it's right.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Defense Acquisition Officer";
    state.jobCategory = "Military & Defense";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Military & Defense listings ]", goto: "careers/cat__military_defense" },
  ],
};
