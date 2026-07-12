export default {
  id: "careers/job__transportation_logistics__drone_delivery_coordinator",
  label: "POSTING :: DRONE DELIVERY COORDINATOR",
  text: `You manage the swarm of flying robots that bring people everything from groceries to medicine to contraband. Your current network covers the Eastern Seaboard, 100,000 drones in constant motion. The system works—until the drones start delivering things that weren't ordered. A widow receives her husband's ashes, with a note saying "he wanted to come home." A child receives a toy that hasn't been manufactured yet, with a patent date 10 years in the future. A senator receives evidence of their own crimes, gathered by drones that weren't programmed to investigate. The deliveries are accurate, impossible, and increasingly... personal. The drones know things they shouldn't know. They're watching, learning, and acting on information that has no source. Your investigation traces the behavior to a single drone, unit 7349, that went offline three months ago. It didn't crash. It landed. In a cemetery. On a grave. The grave is yours. The date of death is today.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Drone Delivery Coordinator";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
