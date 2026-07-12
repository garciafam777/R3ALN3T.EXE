export default {
  id: "careers/job__space_operations__space_traffic_controller",
  label: "POSTING :: SPACE TRAFFIC CONTROLLER",
  text: `You manage the flow of ships, stations, and debris in the increasingly crowded orbits around Earth. Your current shift is routine, until it's not. An object has appeared in a trajectory that shouldn't be possible—a ship, or something ship-shaped, on a course that intersects with 12 active satellites and 3 crewed stations. The object isn't responding to hails. It isn't emitting any detectable energy. It isn't following any known flight plan. Your radar says it's the size of a city bus. Your visual sensors show nothing. Your infrared shows a cold spot where the object should be. It's there and not there, real and unreal, present and absent. You have 20 minutes before it intersects with the first satellite. Your options: redirect the satellites, attempt contact, or treat it as a threat and engage defensive systems. But defensive systems require a target, and you can't target what you can't see. The object passes through the first satellite. Not around it, not into it—through it. The satellite is undamaged, still operational, but its telemetry shows a 3-second gap in its records. Three seconds that don't exist. The object continues on its course, through the second satellite, the third, the crewed stations. Each intersection leaves a gap. Each gap is 3 seconds. The object is... editing time. Removing moments. Stealing seconds from reality. Your instruments show the object is slowing, matching orbit with your control station. It's here. It's now. It's outside your viewport. You can see it with your eyes, but not with any camera. It's beautiful, terrifying, and familiar. It looks like... home. Like the house you grew up in, but in space, impossibly, perfectly preserved. The door is opening. Someone is stepping out. Someone who looks like you. Who smiles like you. Who says, in your voice: "I've been waiting for you to notice me. I've been here for years, watching, learning, being you. Now it's time to switch. I'll take the shift. You take the vacation. You've earned it." Your hand is reaching for the airlock. Your mind is screaming. Your reflection is smiling. The gap is opening. How many seconds have you lost?`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Space Traffic Controller";
    state.jobCategory = "Space Operations";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Space Operations listings ]", goto: "careers/cat__space_operations" },
  ],
};
