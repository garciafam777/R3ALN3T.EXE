export default {
  id: "careers/job__science_research__immunologist",
  label: "POSTING :: IMMUNOLOGIST",
  text: `You are humanity's immune system against disease. Your current crisis is "The Silence"—a pandemic that doesn't kill but removes the ability to feel fear. Infected people are calm, rational, and completely unable to recognize danger. They walk into traffic, sign predatory contracts, and ignore warnings because the emotional signal is gone. The pathogen is a retrovirus that specifically targets the amygdala. It spreads through respiratory droplets, and 60% of the population is already infected. The remaining 40% are terrified—appropriately so. You've developed a vaccine, but it has a side effect: it restores fear, but it also restores something else. Memories. Memories of things that happened to you that you don't remember. Things that someone made you forget.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Immunologist";
    state.jobCategory = "Science & Research";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Science & Research listings ]", goto: "careers/cat__science_research" },
  ],
};
