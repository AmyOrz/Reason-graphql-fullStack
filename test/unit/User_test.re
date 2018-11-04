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

    describe("test init fake database", () => {
      beforeEach(() => UserTableTool.insertDataIntoUser());

      testPromise("test get all user data", () => {
        let getAllUserSource = {|
            {
              users{
                id
                name
                address
              }
            }
          |};

        GraphQL.run(
          AppGraphQLTool.getSchema(),
          getAllUserSource,
          ~rootValue=UserValueTool.getUserValue(),
          (),
        )
        |> Js.Promise.then_(execResult =>
             Js.Promise.resolve(
               expect(execResult##data##users)
               |> toEqual([|
                    {"address": "jinniuqu", "id": "1", "name": "name1"},
                    {"address": "jinniuqu", "id": "2", "name": "name2"},
                    {"address": "jinniuqu", "id": "3", "name": "name3"},
                    {"address": "jinniuqu", "id": "4", "name": "name4"},
                  |]),
             )
           );
      });

      testPromise("test delete specific user", () => {
        let deleteUserSource = {|
              mutation{
                deleteUser(id:"1")
              }
          |};

        GraphQL.run(
          AppGraphQLTool.getSchema(),
          deleteUserSource,
          ~rootValue=UserValueTool.getUserValue(),
          (),
        )
        |> Js.Promise.then_(execResult => {
             let getAllUserSource = {|
            {
              users{
                id
                name
                address
              }
            }
          |};

             GraphQL.run(
               AppGraphQLTool.getSchema(),
               getAllUserSource,
               ~rootValue=UserValueTool.getUserValue(),
               (),
             )
             |> Js.Promise.then_(execResult =>
                  Js.Promise.resolve(
                    expect(execResult##data##users)
                    |> toEqual([|
                         {"address": "jinniuqu", "id": "2", "name": "name2"},
                         {"address": "jinniuqu", "id": "3", "name": "name3"},
                         {"address": "jinniuqu", "id": "4", "name": "name4"},
                       |]),
                  )
                );
           });
      });
    });
  });