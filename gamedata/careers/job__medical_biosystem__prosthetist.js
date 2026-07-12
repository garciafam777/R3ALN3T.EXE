export default {
  id: "careers/job__medical_biosystem__prosthetist",
  label: "POSTING :: PROSTHETIST",
  text: `You build replacement parts for broken bodies. Your current patient is a veteran who lost all four limbs in orbital combat. The prosthetics you design are masterpieces—neurally controlled, sensorially feedback-enabled, stronger and more dexterous than biological limbs. But the patient is rejecting them. Not physically—the integration is perfect. Psychologically. They report that the prosthetics "dream." When they sleep, they experience sensations from the limbs that don't match their own memories: the feeling of holding a child they've never had, of walking on a beach they've never visited, of dying in a war that hasn't happened yet. The prosthetics contain recycled neural tissue from deceased donors. The dreams aren't random. They're memories. And one of the donors was executed for crimes against humanity. The patient is experiencing his victim's final moments. They want the limbs removed. The limbs want to stay.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Prosthetist";
    state.jobCategory = "Medical & Biosystem";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Medical & Biosystem listings ]", goto: "careers/cat__medical_biosystem" },
  ],
};
