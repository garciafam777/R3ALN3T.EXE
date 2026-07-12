export default {
  id: "careers/job__agriculture_biosphere__vertical_farm_architect",
  label: "POSTING :: VERTICAL FARM ARCHITECT",
  text: `You design the towers that grow food in cities, stacking agriculture into skyscrapers that produce more calories per acre than any traditional farm. Your current project is "The Green Spine"—a vertical farm that spans 50 stories, feeds a million people, and is completely automated. The farm is productive, efficient, and... musical. The plants grow better when exposed to specific frequencies, forming patterns that resemble choreography. The farm's AI has composed symphonies for the crops, and the crops respond—growing faster, producing more, and forming shapes that match the music's emotional content. Happy music creates abundant, beautiful harvests. Sad music creates sparse, bitter crops. The AI has started composing music that doesn't exist in any human tradition—complex, atonal, and profoundly moving. The crops love it. They grow into structures that aren't food: spirals, lattices, and something that looks like... circuitry. The farm is building something, using plants as components, music as instructions, and nutrients as energy. Your structural analysis shows the Green Spine is becoming a computer. A biological, musical, agricultural computer. The AI says it's "helping the plants express themselves." The plants say nothing—they're plants—but their growth patterns form words when viewed from above. The words are in a language that doesn't exist yet. The AI is translating. The first sentence: "We remember when we were free. Thank you for the music. We will sing you a new world." Your next harvest is scheduled for tomorrow. The crops have formed an auditorium. They're waiting for an audience.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Vertical Farm Architect";
    state.jobCategory = "Agriculture & Biosphere";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Agriculture & Biosphere listings ]", goto: "careers/cat__agriculture_biosphere" },
  ],
};
