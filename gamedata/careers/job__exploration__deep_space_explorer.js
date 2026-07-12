export default {
  id: "careers/job__exploration__deep_space_explorer",
  label: "POSTING :: DEEP SPACE EXPLORER",
  text: `You venture where no human has gone, into the dark between stars, where the only light is what you bring and the only sound is your own breathing. Your current mission is "The Long Dark"—a 20-year voyage to investigate an anomalous object detected 5 light-years from Earth. The object isn't a planet, isn't a star, isn't anything in the astronomical catalogs. It emits no light, no radiation, no detectable energy. It only reveals itself by what it blocks—the stars behind it are missing, creating a patch of absolute darkness against the cosmic background. You've been traveling for 15 years. The object is getting closer. Your sensors still can't detect it, but you can feel it. The ship's AI reports increased crew anxiety, shared nightmares, and a growing sense of being watched. The nightmares are consistent across all 12 crew members: a vast space, filled with shapes that aren't shapes, sounds that aren't sounds, and a presence that isn't hostile but isn't friendly. It's curious. It's been waiting. It's been waiting for you specifically. The AI suggests turning back. The crew wants to continue. You look at the dark patch where stars should be. It's getting larger. It's not that you're approaching it. It's that it's approaching you. The ship's chronometers are running backward. The AI has stopped speaking. The darkness is speaking now, in a voice that sounds like your own, saying: "You came so far. We're so glad. We've been so alone. Come closer. Let us see you. Let us know you. Let us be known." Your hand is on the thrust control. Forward or back. The darkness waits. It has waited for billions of years. It can wait for your decision.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Deep Space Explorer";
    state.jobCategory = "Exploration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Exploration listings ]", goto: "careers/cat__exploration" },
  ],
};
