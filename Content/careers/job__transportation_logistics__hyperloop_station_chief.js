export default {
  id: "careers/job__transportation_logistics__hyperloop_station_chief",
  label: "POSTING :: HYPERLOOP STATION CHIEF",
  text: `You manage the station where humanity moves at the speed of sound through vacuum tubes. Your current posting is Chicago Hub, the busiest transit point in North America, connecting 40 routes and processing 100,000 passengers daily. The system is flawless—until it isn't. A tube malfunctioned yesterday, trapping a capsule between stations. The passengers were in transit for 4 hours before rescue. They emerged... changed. Not physically—medical scans show no issues. But psychologically. They report experiencing the entire 4 hours as 4 years. They lived full lives in the transit time, built relationships, had children, grew old, and died—then woke up in the rescue chamber. The other passengers in the capsule experienced the same timeline, the same world, the same lives. They remember each other. They mourn their children who never existed. Your company wants to suppress the story. The passengers want to go back. The tube is still malfunctioning. More capsules are getting stuck. More people are living lifetimes in hours. The system is working as designed. The question is: who designed it, and for what?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Hyperloop Station Chief";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
