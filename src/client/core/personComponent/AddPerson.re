type state = {
  name: string,
  sex: string,
};

type action =
  | ChangeName(string)
  | ChangeSex(string);

module AddPerson = [%graphql
  {|

    mutation addUser($name: String!, $sex:String!) {
        addUser( name: $name, sex: $sex)
      }
|}
];
module AddPersonMutation = ReasonApollo.CreateMutation(AddPerson);

module Method = {
  let isValueHasEmpty = state => state.name === "" || state.sex === "";
};

let component = ReasonReact.reducerComponent("AddPerson");

let reducer = (action, state) =>
  switch (action) {
  | ChangeName(value) => ReasonReact.Update({...state, name: value})
  | ChangeSex(value) => ReasonReact.Update({...state, sex: value})
  };

let render = ({state, send}: ReasonReact.self('a, 'b, 'c)) =>
  <AddPersonMutation>
    ...(
         (mutation, {result}) =>
           <div>
             <h1> (DomHelper.textEl("Add Person")) </h1>
             <span className=""> (DomHelper.textEl("name :")) </span>
             <input
               value=state.name
               onChange=(
                 event =>
                   send(
                     ChangeName(
                       ReactDOMRe.domElementToObj(
                         ReactEventRe.Form.target(event),
                       )##value,
                     ),
                   )
               )
             />
             <span className=""> (DomHelper.textEl("sex :")) </span>
             <input
               value=state.sex
               onChange=(
                 event =>
                   send(
                     ChangeSex(
                       ReactDOMRe.domElementToObj(
                         ReactEventRe.Form.target(event),
                       )##value,
                     ),
                   )
               )
             />
             <button
               disabled=(Method.isValueHasEmpty(state))
               onClick=(
                 _ => {
                   let addPersonMutation =
                     AddPerson.make(~name=state.name, ~sex=state.sex, ());

                   mutation(
                     ~variables=addPersonMutation##variables,
                     ~refetchQueries=[|"getAllUser"|],
                     (),
                   )
                   |> ignore;
                 }
               )>
               ("Add a person" |> DomHelper.textEl)
             </button>
             <span>
               (
                 switch (result) {
                 | NotCalled => "" |> DomHelper.textEl
                 | Data(_) => "Person has been added" |> DomHelper.textEl
                 | Error(_) => "ERROR" |> DomHelper.textEl
                 | Loading => "Loading" |> DomHelper.textEl
                 }
               )
             </span>
           </div>
       )
  </AddPersonMutation>;

let make = _children => {
  ...component,
  initialState: () => {name: "", sex: ""},
  reducer,
  render: self => render(self),
};