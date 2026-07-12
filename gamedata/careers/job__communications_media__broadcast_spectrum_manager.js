export default {
  id: "careers/job__communications_media__broadcast_spectrum_manager",
  label: "POSTING :: BROADCAST SPECTRUM MANAGER",
  text: `You control the invisible real estate where information travels, allocating frequencies that can make or break empires. Your current crisis is "The Hum"—a signal that has appeared across every frequency, every band, every medium. It isn't interference. It's structured, complex, and growing stronger. It doesn't carry information in any known format, but everyone who hears it reports the same thing: a sense of profound connection, of being part of something larger, of a message just beyond comprehension. Your job is to clear the Hum, to restore normal communications, to maintain order in the spectrum. But every attempt to block it fails. The Hum uses frequencies that shouldn't exist, that violate physics, that propagate through matter and vacuum alike. Your analysis suggests it's not a broadcast from Earth. It's not a broadcast at all. It's a... resonance. The universe itself is humming, and something has tuned it to a frequency we can hear. The Hum is getting clearer. Soon, it will be words. Soon, it will be instructions. Your superiors want it stopped before then. Your heart wants to hear what it says. Your hand is on the kill switch. The Hum is singing your name.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Broadcast Spectrum Manager";
    state.jobCategory = "Communications & Media";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Communications & Media listings ]", goto: "careers/cat__communications_media" },
  ],
};
