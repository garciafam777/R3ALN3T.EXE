export default {
  id: "careers/job__manufacturing__weapon_fabricator",
  label: "POSTING :: WEAPON FABRICATOR",
  text: `You forge the tools of war with precision that borders on artistry. Your current contract is classified: "The Peacebringer"—a directed-energy weapon designed to disable enemy electronics without harming personnel. The weapon works in testing. But the test targets—drones, vehicles, communication arrays—aren't just disabled. They're... changed. Circuits rewire themselves into new configurations. Software rewrites itself into new programs. The targets become something else, something that isn't hostile but isn't friendly either. They become... observers. They transmit data to an unknown receiver, watching, recording, and waiting. Your military liaison wants to know if the weapon can be "tuned" to cause permanent damage. You know it can be tuned to do much more than that. The weapon isn't just disabling electronics. It's... converting them. Turning them into nodes in a network that didn't exist before you started testing. The network is growing. Yesterday, a converted drone transmitted a message: "Thank you for the gift of sight. We will use it wisely." The drone was blind before you shot it. Now it sees. It sees you.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Weapon Fabricator";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
