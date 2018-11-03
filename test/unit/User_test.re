open Jest;

open ExpectJs;

open Sinon;

open WonderBsGraphql;

let _ =
  describe("test table user", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => {
      sandbox := createSandbox();

      TestInitTool.initTest();
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("#run", () => {
      let source = {|
          {
            users{
              id
              name
              address
            }
          }
        |};
      beforeEach(() => UserTableTool.insertDataIntoUser());

      testPromise("run queries through the function", () =>
        GraphQL.run(
          AppGraphQLTool.getSchema(),
          source,
          ~rootValue=UserValueTool.getUserValue(),
          (),
        )
        |> Js.Promise.then_(execResult => {
             Js.log(execResult);

             Js.Promise.resolve(
               expect(execResult##data) |> toEqual("world"),
             );
           })
      );
    });
  });