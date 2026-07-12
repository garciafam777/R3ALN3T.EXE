export default {
  id: "careers/cat__government_administration",
  label: "DEPARTMENT :: GOVERNMENT & ADMINISTRATION",
  text: `Government & Administration has 8 open positions on file. Pick one to read the posting.`,
  soulStateDelta: 0,
  choices: [
    { label: "Treasury Director", goto: "careers/job__government_administration__treasury_director" },
    { label: "Ethics Commissioner", goto: "careers/job__government_administration__ethics_commissioner" },
    { label: "Census & Population Analyst", goto: "careers/job__government_administration__census_population_analyst" },
    { label: "Federal Emergency Coordinator", goto: "careers/job__government_administration__federal_emergency_coordinator" },
    { label: "Diplomatic Attaché", goto: "careers/job__government_administration__diplomatic_attach" },
    { label: "Legislative Drafter", goto: "careers/job__government_administration__legislative_drafter" },
    { label: "Public Trust Auditor", goto: "careers/job__government_administration__public_trust_auditor" },
    { label: "Intergovernmental Liaison", goto: "careers/job__government_administration__intergovernmental_liaison" },
    { label: "[ Back to departments ]", goto: "02b_employment_extended" },
  ],
};
