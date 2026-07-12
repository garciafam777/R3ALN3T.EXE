export default {
  id: "careers/job__manufacturing__supply_chain_quality_auditor",
  label: "POSTING :: SUPPLY CHAIN QUALITY AUDITOR",
  text: `You verify that what enters the factory is what it claims to be. Your current investigation is "The Ghost Batch"—raw materials that appear in the inventory system but have no corresponding delivery records, no supplier documentation, and no physical presence until they're used in production. The materials are high-quality, often superior to specified alternatives, and they improve the final products in ways that shouldn't be possible. A batch of steel that makes engines 15% more efficient. A shipment of silicon that doubles processor speed. A delivery of organic compounds that cure diseases in the test animals. The ghost batches appear randomly, unpredictably, and always when needed most. Your investigation leads to a loading dock that doesn't exist on any blueprint—a door in the warehouse that opens onto... somewhere else. Through the door, you see a landscape that isn't Earth. A factory, larger than any you've seen, staffed by figures that move wrong, that build things too quickly, that turn to look at you with eyes that reflect no light. They wave. They smile. They push a pallet through the door. The label says: "For our friends. Keep building. We're almost ready." The door closes. The pallet is real. The materials are perfect. Your job is to approve them for use. Your conscience is asking questions you can't answer.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Supply Chain Quality Auditor";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
