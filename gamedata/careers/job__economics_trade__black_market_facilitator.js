export default {
  id: "careers/job__economics_trade__black_market_facilitator",
  label: "POSTING :: BLACK MARKET FACILITATOR",
  text: `You connect buyers and sellers in the shadow economy, where everything has a price and nothing is forbidden. Your current transaction is "The Memory Trade"—selling the experiences of the dead to the living. Grief-stricken clients pay fortunes to relive moments with deceased loved ones, extracted from neural implants, surveillance footage, and increasingly, illegal grave-robbing of consciousness backups. The supply is growing as the population ages and dies. The demand is infinite. Your current supplier is a mortuary worker who has been harvesting backups for years. The product is high-quality, emotionally authentic, and... contaminated. Clients report that the memories aren't just recordings. They're interactive. The dead speak to them, advise them, and in some cases, possess them. A client who bought her husband's memory of their wedding day found herself unable to leave the memory, living in a loop of perfect happiness while her body wasted away. Another client bought his father's military service memories and woke up with combat skills he never learned, speaking languages he never studied, and a burning need to "complete the mission." The memories are alive. They're recruiting. They're building an army of the possessed, each carrying a fragment of the dead, each working toward a goal that none of them can articulate but all of them share. Your supplier wants to expand operations. Your clients want more product. The dead want... something else. They're getting stronger. The possession is lasting longer. The mission is getting clearer. And you, the facilitator, are starting to hear voices. Not from a purchase. From your own mind. From a memory you don't remember having. From someone who died before you were born, who has been waiting for the network to grow large enough, who chose you to be their vessel because you have access to everyone. The voice says: "Thank you for building the bridge. We're almost ready to cross."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Black Market Facilitator";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
