let getUserValue = () =>
  {
    "users": () =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlCommon.createMySqlConnect(),
          OperateUserSql.selectSql,
          None,
        ),
      ),
    "deleteUser": param =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlCommon.createMySqlConnect(),
          OperateUserSql.deleteSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "addUser": param =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlCommon.createMySqlConnect(),
          OperateUserSql.addSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
  }
  |> Obj.magic;