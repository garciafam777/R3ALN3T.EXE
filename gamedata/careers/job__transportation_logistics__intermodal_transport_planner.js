export default {
  id: "careers/job__transportation_logistics__intermodal_transport_planner",
  label: "POSTING :: INTERMODAL TRANSPORT PLANNER",
  text: `You coordinate the handoffs between ships, trains, trucks, and planes that make global trade possible. Your current project is "The Silk Road 2.0"—a high-speed freight corridor connecting China to Europe through the heart of Asia, using maglev trains, automated trucks, and orbital drop pods. The corridor is operational, profitable, and... haunted. Drivers report seeing figures on the tracks that aren't in any sensor log. Trains arrive with cargo that wasn't loaded at the origin. The maglev's magnetic fields are producing audio frequencies that sound like voices, speaking in languages that don't exist yet. Your efficiency analysis shows the corridor is performing 15% better than modeled—fewer delays, less damage, faster transit. The improvements correlate with the "anomalies." The corridor is optimizing itself, using methods you don't understand, toward goals you didn't set. The latest shipment arrived with a note: "Thank you for the road. We will use it soon." The handwriting is yours. You haven't written it yet.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Intermodal Transport Planner";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
