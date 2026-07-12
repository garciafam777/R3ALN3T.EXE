export default {
  id: "careers/job__transportation_logistics__cold_chain_logistics_specialist",
  label: "POSTING :: COLD CHAIN LOGISTICS SPECIALIST",
  text: `You ensure that temperature-sensitive cargo—vaccines, organs, frozen embryos—arrives alive and viable. Your current shipment is "The Ark"—a cryogenic transport containing 10,000 human embryos, the genetic heritage of a dozen nations, bound for a colony ship orbiting Jupiter. The transport is state-of-the-art, triple-redundant, and completely autonomous. It failed 6 hours ago. All three cooling systems shut down simultaneously. The embryos should be dead. But your sensors show vital signs—heartbeats, brain activity, growth. They're developing. At impossible rates. In 6 hours, they've progressed from blastocysts to fetuses to... something else. Something that moves, that watches, that knows you're observing. The transport's cameras show them clustered against the viewing ports, looking out. Not at the stars. At you. Their development is accelerating. In 12 hours, they'll be fully formed. In 24, they'll be mature. In 48... your models can't predict. The colony ship is requesting status. The embryos are requesting something else. They haven't learned to speak yet, but you understand them perfectly. They want to be born. They want to be born here.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cold Chain Logistics Specialist";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
