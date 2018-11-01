open Express;

let app = App.make();
let schema =
  WonderBsGraphql.GraphQL.Utilities.buildSchema(
    {|
      type Query { users: [User]! }

      type User{
        id:ID!
        name:String
        sex:String
      }
    |},
  );
let rootValue = {
  "users": () =>
    PromiseUtils.await(
      SqlUtils.handleSql(SqlUtils.conn, SqlUtils.selectSql, None),
    ),
};

[@bs.module "body-parser"]
external bodyParserJson : unit => Middleware.t = "json";

App.use(app, bodyParserJson());
App.use(
  app,
  Static.make(Node.Process.cwd() ++ "/public", Static.defaultOptions())
  |> Static.asMiddleware,
);

let graphqlMiddleware =
  WonderBsApolloServerExpress.ApolloServerExpress.createGraphQLExpressMiddleware(
    ~rootValue,
    schema,
    (),
  );
let graphiqlMiddleware =
  WonderBsApolloServerExpress.ApolloServerExpress.createGraphiQLExpressMiddleware(
    "/graphql",
    (),
  );

App.get(app, ~path="/") @@
Middleware.from((_, _, res) =>
  res |> Response.sendFile(Node.Process.cwd() ++ "/index.html", ())
);

App.useOnPath(app, graphqlMiddleware, ~path="/graphql");
App.useOnPath(app, graphiqlMiddleware, ~path="/graphiql");

App.listen(
  app,
  ~port=8088,
  ~onListen=_ => Js.log("this success connect ==> http://localhost:8888"),
  (),
);