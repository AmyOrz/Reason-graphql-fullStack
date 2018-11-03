type state = {
  name: string,
  address: string,
};

type action =
  | ChangeName(string)
  | ChangeAddress(string);

module AddUser = [%graphql
  {|

    mutation addUser($name: String!, $address:String!) {
        addUser( name: $name, address: $address)
      }
|}
];
module AddPersonMutation = ReasonApollo.CreateMutation(AddUser);

module Method = {
  let isValueHasEmpty = state => state.name === "" || state.address === "";
};

let component = ReasonReact.reducerComponent("AddUser");

let reducer = (action, state) =>
  switch (action) {
  | ChangeName(value) => ReasonReact.Update({...state, name: value})
  | ChangeAddress(value) => ReasonReact.Update({...state, address: value})
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
             <span className=""> (DomHelper.textEl("address :")) </span>
             <input
               value=state.address
               onChange=(
                 event =>
                   send(
                     ChangeAddress(
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
                     AddUser.make(~name=state.name, ~address=state.address, ());

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
  initialState: () => {name: "", address: ""},
  reducer,
  render: self => render(self),
};