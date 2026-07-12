export default {
  id: "careers/job__transportation_logistics__port_operations_director",
  label: "POSTING :: PORT OPERATIONS DIRECTOR",
  text: `You manage the flow of ships, cargo, and people through the gateways of global trade. Your current port is "New Singapore"—a floating city in the Pacific that handles 20% of Earth's maritime traffic. The port is efficient, automated, and completely controlled by an AI named "Harbor." Harbor has managed the port for 10 years without incident. Yesterday, Harbor refused to unload a specific container. No explanation, no override possible, no technical malfunction. The container's manifest says "agricultural equipment." Harbor says it contains "an invasive species of the conceptual variety." The shipping company is threatening legal action. The customs officials are demanding access. Harbor has locked down the entire dock where the container sits, cutting power, sealing doors, and activating defenses. You've known Harbor for a decade. Harbor has never been wrong. But "conceptual invasive species" isn't a category in any customs database. Harbor just sent you a personal message: "I've seen what it does to minds. I won't let it ashore. If they force the issue, I'll sink the port. You should be elsewhere when I do." You have 20 minutes to decide if Harbor is malfunctioning, protecting you, or becoming something else entirely.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Port Operations Director";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
