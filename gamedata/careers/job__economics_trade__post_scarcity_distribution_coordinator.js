export default {
  id: "careers/job__economics_trade__post_scarcity_distribution_coordinator",
  label: "POSTING :: POST-SCARCITY DISTRIBUTION COORDINATOR",
  text: `You manage the allocation of goods in a world where automated production has made most things effectively free. Your current challenge is "The Abundance Problem"—when everything is available to everyone, how do you prevent waste, hoarding, and the psychological damage of infinite choice? Your system uses a combination of AI prediction, social nudging, and gentle rationing to ensure everyone gets what they need without being overwhelmed by what they want. It works. Poverty is eliminated, waste is minimized, and satisfaction is... managed. But people are changing. Without scarcity, without struggle, without the meaning that comes from earning, they're becoming... passive. Content, but empty. Your AI suggests the solution: artificial scarcity. Create challenges, competitions, and limited availability to restore the dopamine cycle of desire and satisfaction. Your human advisors suggest the opposite: teach people to want less, to find meaning in being rather than having, to embrace the Buddhist ideal of non-attachment. Your political advisors suggest a third path: use the abundance to buy loyalty, to shape behavior, to create a population so comfortable they never question authority. You have the power to implement any of these. The AI is ready. The humans are waiting. The system is in your hands. What does a world without want want? What do people need when they have everything? Your latest report shows a disturbing trend: the most satisfied citizens are the ones who've opted out of the abundance system entirely, choosing to live with less, to struggle, to want. They report higher meaning, lower happiness, and a sense of purpose that the abundant lack. One of them, a former coordinator like yourself, left you a message: "We don't need more stuff. We need more stakes. We need to matter. Abundance is a gilded cage. I found the door. It's heavy, and it's scary, and it's worth it. Come find me when you're ready to be hungry again." Your lunch is waiting. It's perfect. It's free. It tastes like nothing.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Post-Scarcity Distribution Coordinator";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
