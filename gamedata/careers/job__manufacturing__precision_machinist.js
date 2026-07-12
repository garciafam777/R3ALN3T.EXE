export default {
  id: "careers/job__manufacturing__precision_machinist",
  label: "POSTING :: PRECISION MACHINIST",
  text: `You shape metal to tolerances measured in nanometers, crafting components for machines that operate at the edge of possibility. Your current project is "The Core"—a component for an experimental fusion reactor, requiring perfect symmetry and surface finish. The machining is going well, until your tools start producing... patterns. Not errors—deliberate, complex engravings that appear on surfaces that should be featureless. The patterns are microscopic, invisible to the naked eye, but detectable by your quality scanners. They're consistent across all components, regardless of the design, and they match no known symbol system. Your analysis suggests they're... maps. Star maps, showing constellations that don't match Earth's sky. The maps are three-dimensional, showing not just positions but trajectories, dates, and something that looks like... warnings. The final component you machine contains a message, in a language that somehow you understand without learning: "The reactor you're building doesn't generate power. It generates a signal. A beacon. The pattern on this component is the frequency. Turn it on, and they will hear you. Turn it on, and they will come. The choice is yours. We couldn't decide. We left the pattern for someone who could." Your supervisor is asking about the delay. The component is finished. The pattern is perfect. The choice is yours.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Precision Machinist";
    state.jobCategory = "Manufacturing";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Manufacturing listings ]", goto: "careers/cat__manufacturing" },
  ],
};
