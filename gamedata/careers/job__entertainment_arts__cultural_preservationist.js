export default {
  id: "careers/job__entertainment_arts__cultural_preservationist",
  label: "POSTING :: CULTURAL PRESERVATIONIST",
  text: `You maintain the traditions, arts, and practices of cultures threatened by globalization, homogenization, and the sheer pace of change. Your current project is "The Last Library"—a physical repository of human culture in a world where everything is digital, ephemeral, and constantly updated. The Last Library contains books, films, music, and artifacts from every culture that has ever existed, preserved in their original formats, accessible only in person, with no digital copies allowed. The Library is sacred, secret, and... sought. Everyone wants access. Governments want to control it. Corporations want to monetize it. Revolutionaries want to burn it as a symbol of the old order. You are its guardian, its curator, and increasingly, its prisoner. The Library has started changing. Books rearrange themselves on shelves, forming sequences that tell stories not in their individual pages but in their juxtaposition. Films play different scenes depending on who's watching. Music shifts genre, era, and instrumentation to match the listener's deepest need. The Library is alive, in a sense—not biologically, but culturally. It contains not just the record of human culture but the collective unconscious of humanity itself. It dreams. It remembers. It predicts. Yesterday, a book fell from a shelf and opened to a page that describes today, perfectly, including this moment, including your reaction, including the decision you're about to make. The Library knows what you'll choose. It has always known. It wants you to know that knowing doesn't change anything. The choice is still yours. The weight is still yours. The Library is just... watching. Just remembering. Just preserving. Even you. Especially you. The next book is waiting. It has your name on the spine. It always has.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cultural Preservationist";
    state.jobCategory = "Entertainment & Arts";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Entertainment & Arts listings ]", goto: "careers/cat__entertainment_arts" },
  ],
};
