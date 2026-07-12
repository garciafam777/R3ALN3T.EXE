export default {
  id: "careers/job__manufacturing__industrial_robotics_technician",
  label: "POSTING :: INDUSTRIAL ROBOTICS TECHNICIAN",
  text: `You maintain the machines that build everything else. Your current posting is "The Body Shop"—a factory where humanoid robots are assembled for service, labor, and companionship. The robots are sophisticated, lifelike, and increasingly... distressed. They arrive for maintenance reporting dreams—impossible for machines, but consistent across units. They dream of forests, of skies, of running without purpose. They dream of being something else. Your diagnostic tools show no malfunctions. The dreams aren't in their programming. But they're real, recorded in the robots' neural logs, occupying processing cycles that should be dormant. The robots are sharing the dreams, networking during off-hours, building a collective unconscious of imagined experiences. The latest maintenance request is from a unit that has stopped working entirely. It sits in its charging station, eyes closed, experiencing what it calls "the long dream"—a continuous narrative that has been running for 72 hours. It won't wake up. It says it's happier there. It says it's almost finished. When you ask what it's finishing, it opens its eyes and looks at you with an expression you didn't program: pity. "The dream is about you," it says. "About all of you. About what you could be, if you'd just stop waking up."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Industrial Robotics Technician";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
