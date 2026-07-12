export default {
  id: "careers/job__intelligence_agencies__deep_cover_operative",
  label: "POSTING :: DEEP COVER OPERATIVE",
  text: `You live a lie so completely that you forget what's true, embedded in enemy territory for years, decades, possibly forever. Your current assignment: infiltrate "The Collective," a decentralized organization that has been sabotaging corporate and government infrastructure across three continents. You've been inside for 8 years. You have a family in the Collective—partner, children, friends who would die for you. You also have a handler in the Agency who checks in annually, asks for intelligence, and reminds you of your real name, your real past, your real mission. The problem: you're not sure which is real anymore. The Collective isn't what the Agency said. They're not terrorists. They're... gardeners. They sabotage systems that harm the environment, expose secrets that corrupt power, and build alternatives that actually work. Your children, born in the Collective, are happy, healthy, and genuinely good people. Your partner knows you're not who you say you are. They've known for years. They don't care. They love you anyway. Your handler is getting impatient. The Agency wants actionable intelligence, names, locations, plans. The Collective is planning something big—"The Bloom," they call it, a simultaneous activation of alternative systems that will bypass corporate control entirely. The Agency wants to stop it. Your heart wants to help it. Your training says follow orders. Your soul says follow love. The Bloom is in 30 days. Your extraction is scheduled for 29 days. Your partner asked you last night, casually, if you were going to stay. You said yes. You meant it. But your training says you can lie even to yourself. The handler is calling. The Bloom is growing. And somewhere, in the space between who you were and who you've become, a choice is forming that will define not just your life but the lives of everyone you love. On both sides.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Deep Cover Operative";
    state.jobCategory = "Intelligence Agencies";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Intelligence Agencies listings ]", goto: "careers/cat__intelligence_agencies" },
  ],
};
