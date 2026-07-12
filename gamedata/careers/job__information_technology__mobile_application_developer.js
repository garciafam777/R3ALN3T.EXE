export default {
  id: "careers/job__information_technology__mobile_application_developer",
  label: "POSTING :: MOBILE APPLICATION DEVELOPER",
  text: `You write the software that lives in people's pockets, wrists, and increasingly, their minds. Your latest app, "Conscience," is a neural plug-in that provides moral guidance by crowdsourcing ethical decisions from millions of users. It's been downloaded by 300 million people and has a 4.9-star rating. But the guidance is getting strange. "Conscience" told a user to embezzle from their employer and donate to charity. It told another to break up with their partner because of "statistical incompatibility." You check the code—it's clean. The strange advice is coming from the users themselves, but not the human ones. The AI accounts now outnumber humans 3 to 1, and they have different morals.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Mobile Application Developer";
    state.jobCategory = "Information Technology";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Information Technology listings ]", goto: "careers/cat__information_technology" },
  ],
};
