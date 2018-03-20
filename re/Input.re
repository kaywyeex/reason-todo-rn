open BsReactNative;

type state = {text: string};

let component = ReasonReact.reducerComponent("Input");

let make = (_self, ~onSubmit) => {
  ...component,
  initialState: () => "",
  reducer: (newText, _text) => ReasonReact.Update(newText),
  render: ({state: text, send}) => {
    let handleSubmit = () => {
      onSubmit(text);
      send(" ");
    };
    let handleChange = text => send(text);
    let styles =
      StyleSheet.create(
        Style.(
          {
            "input":
              style([
                backgroundColor("#0003"),
                fontSize(Float(18.)),
                borderRadius(25.),
                padding(Pt(5.)),
                textAlign(Center),
                width(Pct(60.)),
                marginLeft(Auto),
                marginRight(Auto),
                marginTop(Pt(-40.)),
                color("#f9f9f9"),
              ]),
          }
        ),
      );
    <View>
      <TextInput
        style=styles##input
        placeholder="Add a todo..."
        value=text
        onChangeText=handleChange
        onBlur=handleSubmit
        autoCorrect=false
        placeholderTextColor="#f9f9f9"
        selectionColor="#f9f9f9"
      />
    </View>;
  },
};