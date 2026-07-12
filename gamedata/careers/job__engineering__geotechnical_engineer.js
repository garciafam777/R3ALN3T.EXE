export default {
  id: "careers/job__engineering__geotechnical_engineer",
  label: "POSTING :: GEOTECHNICAL ENGINEER",
  text: `You understand the ground beneath our feet. Your current project is stabilizing the San Andreas Fault, which has been showing signs of imminent catastrophic rupture. Your solution: inject the fault with a smart polymer that hardens under shear stress, effectively gluing the tectonic plates together. It works. Seismic activity has dropped to historic lows. But the stress is accumulating elsewhere—faults that shouldn't be active are showing movement. The polymer is... migrating. It's spreading through the Earth's crust along channels that don't exist on any geological map. Your sensors detect it 100 miles from the injection site, and it's still moving. Toward Yellowstone. Toward the mid-continent rift. Toward something that wants to stay buried.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Geotechnical Engineer";
    state.jobCategory = "Engineering";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Engineering listings ]", goto: "careers/cat__engineering" },
  ],
};
