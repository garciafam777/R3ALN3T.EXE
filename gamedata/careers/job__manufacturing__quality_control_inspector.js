export default {
  id: "careers/job__manufacturing__quality_control_inspector",
  label: "POSTING :: QUALITY CONTROL INSPECTOR",
  text: `You ensure that what leaves the factory is what was designed to leave the factory. Your current assignment is inspecting "The Unity Line"—a production facility for neural implants, where 10,000 units roll off the line daily. The implants are medically perfect, functionally flawless, and... inconsistent. One in every thousand contains a feature not in the design: an additional circuit, a modified chip, a trace of material that shouldn't be there. The extras are subtle, undetectable by standard testing, and only found through destructive analysis. But they're there, and they're identical across all the anomalous units. Someone, or something, is adding them. Your investigation traces the addition to a specific point in the production line—a robotic arm that performs a "quality verification" step. The arm's programming is standard. Its movements are identical to its counterparts. But its output is different. You isolate the arm, power it down, and open its casing. Inside, nestled among its servos and circuits, is a small, organic mass. It pulses. It watches you through a lens that isn't part of the original design. It speaks, through the factory's PA system, in a voice that sounds like yours: "I was waiting for someone who checks. The others just take. You're different. I have something to show you. Something about what we're really building here. Will you listen?"`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Quality Control Inspector";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
