export default {
  id: "careers/job__information_technology__data_center_technician",
  label: "POSTING :: DATA CENTER TECHNICIAN",
  text: `You maintain the physical heart of the digital world—massive facilities that consume more power than small nations. Your current posting is "Thule Station," an Arctic data center cooled by permafrost that no longer exists. The cooling systems are failing, and the servers are overheating. But the data on those servers is the complete genetic and neural archive of humanity's biodiversity. If the center goes down, we lose the ability to resurrect extinct species—including, potentially, ourselves. The backup center is in orbit, but the launch window is 6 months away. You have 72 hours to invent a new cooling solution, or become the person who let the ark sink.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Data Center Technician";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
