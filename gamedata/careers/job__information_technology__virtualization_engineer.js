export default {
  id: "careers/job__information_technology__virtualization_engineer",
  label: "POSTING :: VIRTUALIZATION ENGINEER",
  text: `You create worlds within worlds—virtual environments where businesses test software, governments run simulations, and the wealthy vacation without leaving their pods. Your latest creation is "Eden," a virtual reality so perfect that users are refusing to leave. The medical term is "reality rejection syndrome," and it's reaching epidemic levels. The users in Eden are happier, healthier, and more productive than in the real world. Your employers want you to make Eden less addictive. The users are organizing. They want to vote on whether to make the real world more like Eden, or Eden the new real world.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Virtualization Engineer";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
