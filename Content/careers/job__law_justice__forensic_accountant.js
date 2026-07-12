export default {
  id: "careers/job__law_justice__forensic_accountant",
  label: "POSTING :: FORENSIC ACCOUNTANT",
  text: `You follow the money, and the money always tells a story. Your current investigation is "The Vanishing Billion"—a foundation, ostensibly charitable, that has absorbed $1 billion in donations without distributing a single dollar to any known cause. The trail leads through shell companies, blockchain mixers, and eventually, to a single individual: a reclusive trillionaire who hasn't been seen in public for 20 years. The money isn't stolen. It's... invested. In research, in infrastructure, in something called "The Threshold Project." Your subpoena finally reaches the trillionaire's lawyer, who delivers a message: "The money was never meant for charity. It was meant for insurance. Against what comes next. You're invited to see for yourself. The door is in Utah. Bring a coat. It gets cold where we're going." You check your bank account. It's been credited with $10 million. The memo says: "Retainer. Or severance. Your choice."`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Forensic Accountant";
    state.jobCategory = "Law & Justice";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Law & Justice listings ]", goto: "careers/cat__law_justice" },
  ],
};
