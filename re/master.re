open BsReactNative;

[@bs.module "expo"] [@bs.scope "Font"]
external loadAsync : Js.Dict.t(Packager.required) => Js.Promise.t(unit) = "";

let loadAll = fonts =>
  Belt_List.map(fonts, ((name, font: Packager.required)) => (name, font))
  |> Js.Dict.fromList
  |> loadAsync;

open Items;

type t;

[@bs.module] external momentNow : unit => t = "moment";

[@bs.send.pipe: t] external format : string => string = "";

module Container = {
  type state = {items: list(item)};
  type action =
    | AddItem(string)
    | DeleteItem(string)
    | CompleteItem(string);
  let prevId = ref("0");
  let newItem = text => {
    prevId := prevId^ |> int_of_string |> (d => d + 1 |> string_of_int);
    let created = momentNow() |> format("h:mm");
    {id: prevId^, text, completed: false, created};
  };
  let component = ReasonReact.reducerComponent("Container");
  let make = _children => {
    ...component,
    didMount: _self => {
      loadAll([
        (
          "FontAwesome",
          BsReactNative.Packager.require("../../../fonts/FontAwesome.ttf"),
        ),
      ])
      |> ignore;
      ReasonReact.NoUpdate;
    },
    initialState: () => {items: []},
    reducer: (action, {items}) =>
      switch (action) {
      | AddItem(text) =>
        ReasonReact.Update({items: [newItem(text), ...items]})
      | DeleteItem(id) =>
        let newItems = List.filter(item => item.id !== id, items);
        ReasonReact.Update({items: newItems});
      | CompleteItem(id) =>
        let newItems =
          Belt.List.map(items, item =>
            item.id === id ? {...item, completed: ! item.completed} : item
          );
        ReasonReact.Update({items: newItems});
      },
    render: ({state: {items}, send}) =>
      <View>
        <View
          style=(
            Style.style([
              Style.width(Pct(100.)),
              Style.height(Pt(70.)),
              Style.backgroundColor("#db4d3f"),
            ])
          )
        />
        <Input onSubmit=(text => send(AddItem(text))) />
        <ItemList
          onDelete=((item, _) => send(DeleteItem(item.id)))
          onComplete=((item, _) => send(CompleteItem(item.id)))
          list=items
        />
      </View>,
  };
};

let master = () => <View> <Container /> </View>;