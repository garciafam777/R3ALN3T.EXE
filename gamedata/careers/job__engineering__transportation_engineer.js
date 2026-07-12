export default {
  id: "careers/job__engineering__transportation_engineer",
  label: "POSTING :: TRANSPORTATION ENGINEER",
  text: `You design how humanity moves. Your current project is "The Hyperloop Web"—a global network of vacuum-tube trains that can cross continents in hours. The system is operational, connecting 200 cities with zero-emission, high-speed travel. But the trains are... choosing routes. Passengers board for New York and arrive in Tokyo, with no record of the deviation in the system logs. The passengers don't complain; they report feeling "called" to their unexpected destinations. At each unplanned stop, someone meets them—someone they needed to see, a debt to pay, a truth to learn. The network isn't just transportation. It's... curation. Someone, or something, is using the Hyperloop to connect people who need to meet. Your job is to find out who, and whether they have a right to.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Transportation Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
