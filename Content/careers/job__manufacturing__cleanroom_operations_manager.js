export default {
  id: "careers/job__manufacturing__cleanroom_operations_manager",
  label: "POSTING :: CLEANROOM OPERATIONS MANAGER",
  text: `You maintain the sterile environments where the most sensitive manufacturing occurs—chips, pharmaceuticals, and materials that can't tolerate a single speck of dust. Your current facility is "The White Room"—a Class-1 cleanroom where quantum processors are assembled, requiring conditions more sterile than a surgical theater. The facility is perfect. Too perfect. The particle counts are zero. Not near-zero, not statistically zero—actually zero. Nothing enters, nothing leaves, nothing changes. The workers report feeling "preserved"—time seems to move differently inside the White Room. A shift feels like minutes; a break feels like hours. The products are flawless, the yields are 100%, and the workers are... fading. They become pale, slow, and detached from the world outside. They speak of "the silence" as a blessing, a refuge from the chaos of the unclean world. Your medical scans show no abnormalities, but the workers' brain activity is decreasing, converging toward a single, uniform pattern. The White Room isn't just clean. It's emptying them. Making them pure. Making them ready. For what, they don't say. They just smile and return to work. The latest batch of quantum processors shows an anomaly: they contain no circuits. Just... space. Empty, perfect, waiting space. The processors work—better than designed—but they don't process information. They process... absence. The buyers are thrilled with the performance. The workers are almost ready. The White Room is almost clean enough. You're the manager. You're responsible. You're starting to feel the silence too.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cleanroom Operations Manager";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
