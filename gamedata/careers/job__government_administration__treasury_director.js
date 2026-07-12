export default {
  id: "careers/job__government_administration__treasury_director",
  label: "POSTING :: TREASURY DIRECTOR",
  text: `You wake up in a climate-controlled government bunker beneath what used to be the Federal Reserve. Your neural implant buzzes with the weight of the nation's synthetic currency reserves. The United States no longer prints paper money—it mints cryptographic trust. Your days are spent balancing the ledgers of a thousand blockchain treasuries, negotiating with corporate city-states for tax compliance, and deciding which failing municipalities get emergency liquidity injections. A faction of secessionist governors wants to establish their own currency. Your choices: enforce federal monetary unity or let the fragments fall and pick up the pieces.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Treasury Director";
    state.jobCategory = "Government & Administration";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Government & Administration listings ]", goto: "careers/cat__government_administration" },
  ],
};
