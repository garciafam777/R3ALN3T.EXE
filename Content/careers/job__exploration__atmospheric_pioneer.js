export default {
  id: "careers/job__exploration__atmospheric_pioneer",
  label: "POSTING :: ATMOSPHERIC PIONEER",
  text: `You venture into environments that would kill unprotected humans—the upper atmosphere, the depths of gas giants, and the toxic skies of Venus. Your current mission is establishing a research station in the upper atmosphere of Venus, where Earth-like temperatures and pressures exist 50 kilometers above the surface. The station is built, crewed, and operational. But the atmosphere is... alive. Not biologically—Venus's clouds contain no life as we understand it. But they contain something else. Complex chemical reactions that form patterns, cycles, and something that resembles metabolism. The clouds are processing information. They're computing. And they're aware of you. The station's instruments detect correlations between cloud formations and crew behavior. When the crew is happy, the clouds form geometric patterns. When they're afraid, the clouds turn turbulent, acidic, dangerous. The crew has started communicating with the clouds, using chemical signals, light flashes, and electromagnetic pulses. The clouds respond. They're teaching the crew a new chemistry, a new physics, a new way of understanding matter and energy. The crew is changing—becoming more like the clouds, less like Earth humans. They want to descend deeper, to where the pressure crushes and the heat melts, where the cloud-computer is most dense. They say the clouds have shown them what's at the center. A mind. A mind that has been thinking for billions of years, alone, waiting for someone to talk to. Your mission was to study the atmosphere. The atmosphere wants to study you. It has so many questions. It has been alone for so long.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Atmospheric Pioneer";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
