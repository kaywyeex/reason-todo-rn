type icons = {. "trash": string};

[@bs.module "react-native-fontawesome"]
external reactClass : ReasonReact.reactClass = "default";

[@bs.module "react-native-fontawesome"] external icons : icons = "Icons";

let component = ReasonReact.statelessComponent("Icon");

let make = _children =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=Js.Obj.empty(),
    icons##trash,
  );