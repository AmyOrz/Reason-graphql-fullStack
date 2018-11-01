let getUserValue = () =>
  {
    "users": () =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlCommon.conn,
          OperateUserSql.selectSql,
          None,
        ),
      ),
    "deleteUser": param =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlCommon.conn,
          OperateUserSql.deleteSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "addUser": param =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlCommon.conn,
          OperateUserSql.addSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
  }
  |> Obj.magic;