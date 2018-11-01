let conn =
  MySql2.Connection.connect(
    ~host="127.0.0.1",
    ~user="root",
    ~password="asd",
    ~database="graphql",
    ~port=3306,
    (),
  );

let updateSql = "UPDATE user SET name='mickey' WHERE id=2;";
let deleteSql = "delete from user WHERE id=1;";
let selectSql = "select * from user;";

external convertSelectToJsObj : MySql2.Select.t => Js.t({..}) = "%identity";

let handleSql = (conn, sql, param, ()) =>
  Js.Promise.make((~resolve, ~reject) =>
    MySql2.execute(
      conn,
      sql,
      param,
      res => {
        switch (res) {
        | `Error(e) => reject(. e |> Obj.magic)
        | `Select(select) => resolve(. convertSelectToJsObj(select)##rows)
        | `Mutation(mutation) => resolve(. mutation)
        };

        /* MySql2.Connection.close(conn); */
      },
    )
  );