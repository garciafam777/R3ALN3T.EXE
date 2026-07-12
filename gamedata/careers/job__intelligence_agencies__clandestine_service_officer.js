export default {
  id: "careers/job__intelligence_agencies__clandestine_service_officer",
  label: "POSTING :: CLANDESTINE SERVICE OFFICER",
  text: `You run operations in denied areas, places where your government has no official presence and your existence is a legal fiction. Your current operation is in "The Free Zone"—a region of the Pacific Ocean where no nation claims sovereignty, where corporations rule directly, and where the laws are written by those with the most guns. Your mission: establish a network of assets, gather intelligence on corporate activities, and prepare for potential military intervention. The Free Zone is violent, profitable, and... free. Not in the political sense, but in the existential sense. People here have shed the identities they had in the civilized world. They're not citizens, employees, or subjects. They're just... people. Making choices, taking risks, living and dying by their own decisions. Your assets aren't assets. They're friends. Your intelligence isn't intelligence. It's understanding. The corporate activities you're supposed to monitor aren't crimes. They're experiments in governance, in economy, in human organization. The Free Zone is ugly, brutal, and alive in a way that the managed world isn't. Your handler wants reports, names, actionable intelligence. You want to understand why the Free Zone works, why people choose it, why freedom—even dangerous freedom—is so attractive. Your reports have become... sympathetic. Your handler is suspicious. Your assets have noticed. They offer you a choice: complete the mission, betray them to your government, return to a world of orders and obedience. Or stay. Become one of them. Live freely, dangerously, meaningfully. The corporate security forces are closing in. Your extraction window is closing. The Free Zone is burning, as it always does, as it always has, as a consequence of its own chaos. But from the ashes, something always rises. Something new. Something free. Your handler is screaming in your ear. Your friends are waiting with a boat. The fire is getting closer. And somewhere, in the space between duty and desire, between safety and meaning, a life is being chosen. Your life. The only one you have. The only one you can live.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Clandestine Service Officer";
    state.jobCategory = "Intelligence Agencies";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Intelligence Agencies listings ]", goto: "careers/cat__intelligence_agencies" },
  ],
};
