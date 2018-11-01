type state = {id: string};

type action =
  | Change(string);

module DeleteUser = [%graphql
  {|
    mutation deleteUser($id: ID!) {
        deleteUser(id: $id)
      }
|}
];
module DeleteUserMutation = ReasonApollo.CreateMutation(DeleteUser);


let component = ReasonReact.reducerComponent("DeleteUser");

let reducer = (action, state) =>
  switch (action) {
  | Change(value) => ReasonReact.Update({...state, id: value})
  };

let render = ({state, send}: ReasonReact.self('a, 'b, 'c)) =>
  <DeleteUserMutation>
    ...(
         (mutation, {result}) =>
           <div>
             <h1> ("Delete a Person By Id" |> DomHelper.textEl) </h1>
             <input
               value=state.id
               onChange=(
                 event =>
                   send(
                     Change(
                       ReactDOMRe.domElementToObj(
                         ReactEventRe.Form.target(event),
                       )##value,
                     ),
                   )
               )
             />
             <button
               disabled=(state.id === "")
               onClick=(
                 _ => {
                   let deletePersonMutation =
                     DeleteUser.make(~id=state.id, ());

                   mutation(
                     ~variables=deletePersonMutation##variables,
                     ~refetchQueries=[|"getAllUser"|],
                     (),
                   )
                   |> ignore;
                 }
               )>
               ("Delete a person" |> ReasonReact.string)
             </button>
             <span>
               (
                 switch (result) {
                 | NotCalled =>
                   Js.log("Not called");
                   "" |> DomHelper.textEl;
                 | Data(d) =>
                   Js.log2("data", d);
                   "Person has been deleted" |> DomHelper.textEl;
                 | Error(e) =>
                   Js.log2("error", e);
                   "ERROR" |> DomHelper.textEl;
                 | Loading =>
                   Js.log("Loading");
                   "Loading" |> DomHelper.textEl;
                 }
               )
             </span>
           </div>
       )
  </DeleteUserMutation>;

let make = _children => {
  ...component,
  initialState: () => {id: ""},
  reducer,
  render: self => render(self),
};