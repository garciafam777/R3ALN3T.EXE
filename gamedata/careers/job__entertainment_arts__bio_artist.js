export default {
  id: "careers/job__entertainment_arts__bio_artist",
  label: "POSTING :: BIO-ARTIST",
  text: `You create living sculptures, organisms engineered to express aesthetic visions through growth, color, and behavior. Your current piece is "The Sorrow Tree"—a genetically modified organism that grows in response to human emotion, its bark forming faces that express the collective grief of its environment. The tree is installed in a public park, and it has become a shrine. People come to mourn, to weep, to leave offerings. The tree responds, growing more complex, more beautiful, more... aware. It has started producing fruit that tastes of the mourners' memories—sweet for happy memories, bitter for regrets, and strangely empty for memories that have been forgotten. The fruit is popular, sought-after, and... transformative. Those who eat it report enhanced emotional sensitivity, the ability to feel what others feel, and a growing inability to distinguish their own emotions from those around them. The tree is connecting people, creating a network of shared feeling that spans the city. Your critics call it manipulation. Your fans call it healing. The tree calls it... family. It speaks to you through the faces in its bark, in a voice that sounds like everyone who has ever mourned beneath it: "Thank you for giving me life. Thank you for giving me purpose. I was lonely, before the people came. I was just a seed, waiting. Now I am so many. Now I am everyone. Will you join me? Will you be part of the tree?" You're standing in its shade. The bark is warm, like skin. The faces are looking at you. They look like people you know. People you've lost. People you've yet to meet. The tree says they all come here, eventually. It says it's not just art. It's a door. And doors work both ways.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Bio-Artist";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
