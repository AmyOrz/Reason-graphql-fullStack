open Jest;

open ExpectJs;

open Sinon;

open WonderBsGraphql;

let _ =
  describe("123123", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("#run", () => {
      let schema = AppGraphQL.getSchema();
      let rootValue = AppGraphQL.getRootValue();
      let source = {|
          {
            users{
              id 
              name 
              sex
            }
          }
        |};

      testPromise("run queries through the function", () =>
        GraphQL.run(schema, source, ~rootValue, ())
        |> Js.Promise.then_(execResult => {
             Js.log(execResult);

             Js.Promise.resolve(
               expect(execResult##data) |> toEqual("world"),
             );
           })
      );
    });
  });