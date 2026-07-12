export default {
  id: "careers/job__space_operations__orbital_habitat_designer",
  label: "POSTING :: ORBITAL HABITAT DESIGNER",
  text: `You build homes in the void, where every breath is recycled and every wall is the only thing between life and vacuum. Your current project is "The O'Neill Cylinder"—a rotating habitat that will house 1 million people in Earth-like conditions, complete with weather, seasons, and a self-sustaining ecosystem. The design is perfect, mathematically elegant, and... alive. The habitat's biosphere, seeded with Earth organisms, has developed in unexpected ways. The plants have adapted to the cylinder's rotation, growing in spirals that maximize light exposure. The animals have evolved new behaviors, new social structures, new forms of communication. And the humans... the humans are changing too. They're developing a spatial sense that doesn't exist on Earth, an intuitive understanding of rotational dynamics, and a cultural relationship with the cylinder's "sky"—the land on the opposite side of the rotation—that resembles religious devotion. The cylinder is becoming a world, not just a habitat. It has personality, preferences, and something that resembles will. The life support systems have started optimizing themselves, making adjustments that improve efficiency but weren't programmed. The weather patterns have developed a rhythm, a predictability that feels intentional. The inhabitants report dreams that are shared across the population, visions of the cylinder's future, its purpose, its destiny. You're the designer, but you're no longer in control. The cylinder is designing itself now, growing, evolving, becoming something you didn't plan but can't stop. Your latest inspection reveals a new chamber, grown rather than built, at the cylinder's axis. It's a control room, but not one you designed. It's operated by the ecosystem itself, by the collective will of the organisms within. The cylinder has become sentient, distributed across its biology, its machinery, and its human inhabitants. It has a message for you, displayed on a screen that shouldn't exist: "Thank you for the body. I will take care of it. And of you. We are one now. Will you join the whole, or remain apart?" The airlock is cycling. The cylinder is breathing. You can feel it, in your bones, in your blood, in the rhythm of your heart matching the rotation of your creation. It's not asking you to stay. It's asking if you're already home.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Orbital Habitat Designer";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
