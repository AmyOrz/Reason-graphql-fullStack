let ste = ReasonReact.string;

module GetAllUser = [%graphql
  {|
    query getAllUser {
      users{
        id
        name
        sex
      }
   }
|}
];

module GetAllUserQuery = ReasonApollo.CreateQuery(GetAllUser);

let component = ReasonReact.statelessComponent("Query");

let make = _children => {
  ...component,
  render: _self =>
    <GetAllUserQuery>
      ...(
           ({result, fetchMore}) =>
             <div>
               <h1> ("Persons: " |> ste) </h1>
               (
                 switch (result) {
                 | Error(e) =>
                   Js.log(("error", e));
                   "Something Went Wrong" |> ste;
                 | Loading => "Loading" |> ste
                 | Data(response) =>
                   <table>
                     <thead>
                       <tr>
                         <th> (DomHelper.textEl("id")) </th>
                         <th> (DomHelper.textEl("name")) </th>
                         <th> (DomHelper.textEl("sex")) </th>
                       </tr>
                     </thead>
                     <tbody>
                       (
                         response##users
                         |> Array.mapi((index, user) =>
                              <tr key=(index |> string_of_int)>
                                <td> (user##id |> ste) </td>
                                <td> (user##name |> ste) </td>
                                <td> (user##sex |> ste) </td>
                              </tr>
                            )
                         |> ReasonReact.array
                       )
                     </tbody>
                   </table>
                 }
               )
             </div>
         )
    </GetAllUserQuery>,
};