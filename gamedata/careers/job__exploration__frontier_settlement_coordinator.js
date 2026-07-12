export default {
  id: "careers/job__exploration__frontier_settlement_coordinator",
  label: "POSTING :: FRONTIER SETTLEMENT COORDINATOR",
  text: `You establish human presence in places that have never known it—the Martian highlands, the asteroid belt, the dark side of the moon. Your current project is "New Plymouth"—the first permanent settlement on Titan, Saturn's largest moon, where methane lakes and a thick atmosphere offer resources and protection. The settlement is built, populated by 500 pioneers, and... lonely. The distance from Earth, the time delay in communications, the alien landscape—it creates a psychological pressure that no one anticipated. The settlers are forming cults, not out of religious fervor, but out of desperate need for meaning in an empty world. They worship the methane storms. They personify the cryovolcanoes. They've developed rituals around the 16-day Titan rotation, creating a calendar that has no relationship to Earth's. Your job is to maintain order, productivity, and connection to Earth. But the settlers don't want Earth anymore. They've started calling Titan "home" with a sincerity that worries mission control. They've discovered something in the methane lakes—structures, regular, artificial, ancient. Not built by humans. Not built by anything from Earth. The structures are active, emitting signals that the settlers can feel in their bones, in their dreams, in their growing certainty that they were meant to come here. That Titan was waiting for them. That the structures are... welcoming. Mission control wants the structures investigated, documented, and left alone. The settlers want to move into them. They say the structures are warm inside. They say the air is breathable. They say there's a garden, with plants that sing. Your coordinates are in the settlement's database. The settlers have prepared a room for you. They say the structures told them you were coming.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Frontier Settlement Coordinator";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
