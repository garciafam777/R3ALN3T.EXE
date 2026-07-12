export default {
  id: "careers/job__economics_trade__interplanetary_trade_negotiator",
  label: "POSTING :: INTERPLANETARY TRADE NEGOTIATOR",
  text: `You broker deals between worlds separated by light-minutes, cultural chasms, and the fundamental fact that what's valuable on Earth may be worthless on Mars and vice versa. Your current negotiation is between the Martian Collective and the Earth Consortium over water rights—Mars has ice; Earth has the infrastructure to melt and transport it. The deal should be simple. It isn't. The Martians don't want money. They want... people. Specifically, they want the right to recruit Earth citizens for "cultural exchange programs" that last 20 years and involve significant neural modification. The Consortium is considering it. Unemployment is high, Earth's population is restless, and the Martians are offering technology in addition to water. Your job is to find the compromise that serves both sides. But the Martians aren't telling you everything. Their "cultural exchange" involves more than modification. It involves... replacement. The recruits come back looking the same, sounding the same, but thinking differently. They're calmer, more cooperative, and subtly loyal to Martian interests. Earth has sent 10,000 recruits. 8,000 came back. The 2,000 who didn't were "integrated" into Martian society. The 8,000 who did are advocating for closer Earth-Mars ties, more exchanges, and eventual political union. Your neural scan shows no coercion, no manipulation, no violation of consent. The recruits chose this. They wanted to change. They wanted to be better. The Martians are offering you a spot in the next exchange. They say you'd be perfect for their diplomatic corps. They say you already think like them. They're not wrong. You've been negotiating their position so long, you can't remember why you ever disagreed.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Interplanetary Trade Negotiator";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
