export default {
  id: "careers/job__economics_trade__resource_extraction_economist",
  label: "POSTING :: RESOURCE EXTRACTION ECONOMIST",
  text: `You calculate the value of things that can't be replaced—rare earth elements, helium-3, and the last untouched wilderness. Your current analysis is "The Luna Rush"—the economic impact of asteroid mining on Earth's resource markets. The numbers are staggering: platinum-group metals that would crash the jewelry market, water that would end scarcity, and rare elements that would enable technologies currently impossible. But the extraction has side effects. The asteroids aren't just rock. They're... dormant. Some contain structures, fossils, and evidence of past activity that doesn't match any natural process. Your economic model includes a variable you can't quantify: "heritage value." What is the price of destroying evidence that we aren't alone? What is the cost of mining a grave? The mining corporations want the heritage variable set to zero. The scientific community wants it set to infinity. Your model suggests the truth is somewhere in between—but "somewhere in between" means some asteroids get mined and some get preserved, and the choice of which is which will shape humanity's relationship with the cosmos for millennia. Your latest calculation shows that one specific asteroid, rich in platinum but covered in ruins, would yield $50 trillion in metals. The ruins contain a library, intact, written in a language that your AI translators are beginning to understand. The first translated text is a warning: "Do not take what is not given. The last species that mined this place is dust. We left the warning for those who follow. We hope you are wiser. We hope you are kinder. We hope you are not us." The mining fleet is 48 hours from launch. Your recommendation will determine whether they go. The ruins are waiting. The platinum is waiting. Your calculator is waiting.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Resource Extraction Economist";
    state.jobCategory = "Economics & Trade";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Economics & Trade listings ]", goto: "careers/cat__economics_trade" },
  ],
};
