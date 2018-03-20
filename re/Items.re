open BsReactNative;

type item = {
  id: string,
  text: string,
  completed: bool,
  created: string,
};

module ListItem = {
  let component = ReasonReact.statelessComponent("ListItem");
  let make = (~item, ~onDelete, ~onComplete, ~index, _children) => {
    ...component,
    render: _self => {
      let isEven = n => n mod 2 === 0;
      let styles =
        StyleSheet.create(
          Style.(
            {
              "item":
                style([
                  height(Pt(32.)),
                  width(Pct(100.)),
                  flexDirection(Row),
                  justifyContent(SpaceBetween),
                  backgroundColor(index |> isEven ? "#f9f9f9" : "#db4d3f"),
                  paddingLeft(Pt(8.)),
                  paddingRight(Pt(8.)),
                ]),
              "wrapper": style([flexDirection(Row)]),
              "text":
                style([
                  fontSize(Float(18.)),
                  height(Pt(32.)),
                  lineHeight(32.),
                  textDecorationColor(
                    index |> isEven ? "#db4d3f" : "#f9f9f9",
                  ),
                  color(index |> isEven ? "#db4d3f" : "#f9f9f9"),
                  textDecorationLine(item.completed ? LineThrough : None),
                  textDecorationStyle(Solid),
                ]),
              "date":
                style([
                  fontSize(Float(14.)),
                  height(Pt(32.)),
                  lineHeight(32.),
                  marginRight(Pt(8.)),
                  color(index |> isEven ? "#db4d3f" : "#f9f9f9"),
                ]),
              "icon":
                style([
                  fontSize(Float(24.)),
                  color(index |> isEven ? "#db4d3f" : "#f9f9f9"),
                ]),
              "iconContainer":
                style([alignItems(Center), justifyContent(Center)]),
            }
          ),
        );
      <TouchableOpacity onPress=onComplete>
        <View style=styles##item>
          <Text style=styles##text>
            (ReasonReact.stringToElement(item.text))
          </Text>
          <View style=styles##wrapper>
            <Text style=styles##date>
              (ReasonReact.stringToElement(item.created))
            </Text>
            <TouchableOpacity onPress=onDelete style=styles##iconContainer>
              <Text style=styles##icon> <Icon /> </Text>
            </TouchableOpacity>
          </View>
        </View>
      </TouchableOpacity>;
    },
  };
};

module ItemList = {
  let component = ReasonReact.statelessComponent("ItemList");
  let make = (~list, ~onDelete, ~onComplete, _children) => {
    ...component,
    render: _self =>
      <View>
        (
          ReasonReact.arrayToElement(
            Array.of_list(
              List.mapi(
                (i, item) =>
                  <ListItem
                    onDelete=(onDelete(item))
                    onComplete=(onComplete(item))
                    item
                    key=item.id
                    index=i
                  />,
                list,
              ),
            ),
          )
        )
      </View>,
  };
};