let ste = ReasonReact.string;

module GetAllPersons = [%graphql
  {|
    query getUsers {
      users{
        id
        name
        sex
      }
   }
|}
];

module GetAllPersonsQuery = ReasonApollo.CreateQuery(GetAllPersons);

let component = ReasonReact.statelessComponent("Query");

let make = _children => {
  ...component,
  render: _self =>
    <GetAllPersonsQuery>
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
                   <div>
                     (
                       response##users
                       |> Array.mapi((index, user) =>
                            <div key=(index |> string_of_int)>
                              (user##name |> ste)
                              <br />
                              <p> ("ID: " ++ user##id |> ste) </p>
                              <br />
                              <p> ("sex: " ++ user##sex |> ste) </p>
                            </div>
                          )
                       |> ReasonReact.array
                     )
                     <button
                       onClick=(
                         _ =>
                           fetchMore(
                             ~updateQuery=
                               (prev, _next) =>
                                 /* Update Apollo Store with [@bs.raw {||}] for now, since the type comming in is a generic Js.Json.t for now*/
                                 prev,
                             (),
                           )
                           |> ignore
                       )>
                       ("fetchMore" |> ReasonReact.string)
                     </button>
                   </div>
                 }
               )
             </div>
         )
    </GetAllPersonsQuery>,
};