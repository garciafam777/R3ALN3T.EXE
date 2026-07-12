export default {
  id: "careers/job__transportation_logistics__last_mile_delivery_specialist",
  label: "POSTING :: LAST-MILE DELIVERY SPECIALIST",
  text: `You bridge the final gap between warehouse and doorstep, the most expensive and complex mile in logistics. Your current operation uses a fleet of autonomous ground robots, human couriers, and experimental "matter printers" that can assemble small items on-site from raw materials. The system works—99% of deliveries arrive within the promised window. The 1% that don't... arrive elsewhere. A package meant for Apartment 4B arrives in a sealed bunker beneath the city, addressed to "The Future Occupant." A meal kit arrives at a homeless encampment, containing ingredients that perfectly match the dietary needs of a specific individual who didn't order it. A replacement part arrives at a factory that hasn't broken yet, preventing a catastrophic failure that would have occurred 48 hours later. Your tracking algorithms can't explain the reroutes. The delivery bots report no anomalies. But their GPS logs show them visiting locations that don't exist, following routes that pass through walls, and spending time in transit that exceeds the speed of light. Your customers are satisfied. Your bosses are thrilled. You're terrified because yesterday, a package arrived at your door. It contains a photograph of you, dead, in a location you've never been. The postmark is tomorrow.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Last-Mile Delivery Specialist";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
