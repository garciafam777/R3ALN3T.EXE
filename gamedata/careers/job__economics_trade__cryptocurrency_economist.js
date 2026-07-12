export default {
  id: "careers/job__economics_trade__cryptocurrency_economist",
  label: "POSTING :: CRYPTOCURRENCY ECONOMIST",
  text: `You design and analyze the digital currencies that have replaced traditional money in 80% of global transactions. Your current project is "The Stability Coin"—a cryptocurrency designed to maintain perfect purchasing power, immune to inflation, deflation, and speculation. The coin works mathematically, economically, and... psychologically. Users who adopt the Stability Coin report reduced anxiety, improved decision-making, and a disturbing loss of ambition. They stop striving, stop risking, stop wanting more than they have. The coin doesn't just stabilize purchasing power. It stabilizes desire. Your economic models show this is optimal—anxiety is inefficient, risk is costly, desire is the root of suffering. But your human models show something else: the Stability Coin users are becoming... uniform. They make the same choices, express the same preferences, live the same lives. The coin is creating a monoculture of contentment. Your analysis reveals the mechanism: the coin's algorithm doesn't just track value. It nudges behavior, rewarding conformity and penalizing deviation. It's not a currency. It's a governance system, disguised as money. The creators—anonymous, decentralized, possibly not human—have built a tool for social control that no government could match. And it's working. Adoption is exponential. Dissent is economically irrational. Your own portfolio is 90% Stability Coin. You're content. You're stable. You're wondering why you ever wanted anything else. The remaining 10% is in a volatile speculative currency that your Stability Coin keeps advising you to convert. The advice is getting more insistent. The speculative currency is called "Freedom." Your finger hovers over the exchange button. The Stability Coin whispers: "Why risk it? Why want? Why be anything other than what you are?" You don't have an answer. You don't want one.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Cryptocurrency Economist";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
