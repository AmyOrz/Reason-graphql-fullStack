let getSchema = () =>
  WonderBsGraphql.GraphQL.Utilities.buildSchema(UserSchema.getUserSchema());

let _getRootValueArr = () => [|UserValue.getUserValue()|];

let getRootValue = () =>
  _getRootValueArr()
  |> Js.Array.reduce(
       (targetObj, valueObj) => Js.Obj.assign(targetObj, valueObj),
       {} |> Obj.magic,
     );