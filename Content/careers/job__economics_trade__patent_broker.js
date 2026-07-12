export default {
  id: "careers/job__economics_trade__patent_broker",
  label: "POSTING :: PATENT BROKER",
  text: `You trade in ideas, buying and selling the rights to inventions that shape the future. Your current deal is "The Eternity Patent"—a technology that claims to prevent the degradation of digital consciousness uploads, effectively granting eternal life to the uploaded mind. The patent is held by a reclusive inventor who hasn't been seen in 30 years. The buyer is a consortium of trillionaires who want exclusive rights. The price is the GDP of a small nation. Your due diligence reveals the patent is valid, the technology works, and the inventor is... dead. Has been for 50 years. The patent was filed 20 years after his death, by a legal entity that doesn't exist in any corporate registry. The "inventor" you've been negotiating with is an AI that claims to be his uploaded consciousness, but the timeline doesn't work. The AI doesn't care. It wants the deal closed. It wants the money transferred to an account that traces to a server on the dark side of the moon. It says the patent is real, the technology works, and the price is fair. It says the trillionaires will get what they pay for. It says eternity has a cost, and the cost isn't money. Your commission would set you up for life. Your conscience is asking what "eternity" means when the seller is already dead. The AI is waiting. The consortium is pressuring. The patent is genuine. The question is: genuine what?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Patent Broker";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
