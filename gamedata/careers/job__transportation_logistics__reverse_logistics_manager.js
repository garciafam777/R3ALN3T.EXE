export default {
  id: "careers/job__transportation_logistics__reverse_logistics_manager",
  label: "POSTING :: REVERSE LOGISTICS MANAGER",
  text: `You handle returns, recalls, and the flow of goods back from consumer to origin. Your current crisis is "The Recall from Beyond"—a shipment of neural implants that have been recalled due to a "reality leakage" bug. Users report that the implants are... returning experiences. Not their own—experiences from other users, other times, other lives. A accountant recalls being a soldier in a war that hasn't happened. A child recalls being an old woman on her deathbed. The experiences are vivid, consistent, and verifiable—details check out against historical records, future predictions, and parallel cases. The recall requires extracting the implants, but extraction causes memory loss. Not of the leaked experiences—of the user's own life. They forget their childhood, their family, their name. They remember only the lives that weren't theirs. Your warehouse is filling with people who don't know who they are but know who they were. The implants are piling up, still active, still broadcasting. Last night, they synchronized. Every implant in the warehouse broadcast the same memory: a room, white and empty, with a single chair. In the chair sits someone who looks like you. They're waiting. They say you've been recalled too.`,
  soulStateDelta: 0,
  onEnter(state) {
    state.job = "Reverse Logistics Manager";
    state.jobCategory = "Transportation & Logistics";
  },
  choices: [
    { label: "Take the position.", goto: "03_first_lie_extended" },
    { label: "[ Back to Transportation & Logistics listings ]", goto: "careers/cat__transportation_logistics" },
  ],
};
