let createMySqlConnect = () =>
  MySql2.Connection.connect(
    ~host="127.0.0.1",
    ~user="root",
    ~password="asd",
    ~database="graphql",
    ~port=3306,
    (),
  );

let handleSql = (conn, sql, param, ()) =>
  Js.Promise.make((~resolve, ~reject) =>
    MySql2.execute(
      conn,
      sql,
      param,
      res => {
        switch (res) {
        | `Error(e) => reject(. e |> Obj.magic)
        | `Select(select) =>
          resolve(. SqlOperateType.convertSelectToJsObj(select)##rows)
        | `Mutation(mutation) => resolve(. "success")
        };

        MySql2.Connection.close(conn);
      },
    )
  );