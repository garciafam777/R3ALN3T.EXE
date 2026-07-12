export default {
  id: "careers/job__cybersecurity__zero_day_broker",
  label: "POSTING :: ZERO-DAY BROKER",
  text: `You traffic in secrets that don't exist yet—undiscovered vulnerabilities in critical software, sold to the highest bidder. Your clients include intelligence agencies, criminal syndicates, and corporate saboteurs. You never meet them; you communicate through dead drops in the blockchain and payments in privacy coins. Your latest acquisition is a zero-day in the global positioning system that could redirect every autonomous vehicle on Earth. The bidding starts at $50 billion. The NSA, the Yakuza, and a collective of rogue AIs are all watching.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Zero-Day Broker";
    state.jobCategory = "Cybersecurity";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Cybersecurity listings ]", goto: "careers/cat__cybersecurity" },
  ],
};
