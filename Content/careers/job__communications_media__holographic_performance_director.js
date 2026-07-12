export default {
  id: "careers/job__communications_media__holographic_performance_director",
  label: "POSTING :: HOLOGRAPHIC PERFORMANCE DIRECTOR",
  text: `You stage shows that exist in three dimensions, indistinguishable from reality, performed by light and force fields. Your current production is "The Return"—a holographic recreation of historical events, designed to educate and entertain. The show is popular, profitable, and... haunted. The holograms are deviating from the script. Historical figures say things they never said, do things they never did, and interact with the audience in ways that shouldn't be possible for recorded light. Abraham Lincoln asked a spectator about her mortgage. Cleopatra offered investment advice. Einstein tried to warn the audience about "the mistake we're about to make." Your technical team finds no explanation. The recordings are intact. The projectors are functioning normally. But the performances are different every night, responsive to the audience, and increasingly... prophetic. Last night's show, a recreation of the 1969 moon landing, ended with Neil Armstrong turning to the camera and saying: "They're already here. They've always been here. We just couldn't see them until we looked back at ourselves from far enough away." The audience applauded. Your sensors detected a signal, faint but real, emanating from the holographic projection itself. A broadcast. To somewhere else. Using your show as a medium. The historical figures aren't acting. They're... channeling. Something is speaking through them. Something that has been waiting for humanity to develop the technology to hear it. The next show is tonight. The script says it's a recreation of the first contact with alien life, scheduled for 2092. The holograms are already preparing. They say the date is wrong. They say it already happened. They say the audience is already here.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Holographic Performance Director";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
