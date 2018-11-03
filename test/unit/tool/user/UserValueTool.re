let getUserValue = () =>
  {
    "users": () =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlInitTool.createFakeMySqlConnect(),
          OperateUserSql.selectSql,
          None,
        ),
      ),
    "deleteUser": param =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlInitTool.createFakeMySqlConnect(),
          OperateUserSql.deleteSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "addUser": param =>
      PromiseUtils.await(
        MysqlCommon.handleSql(
          MysqlInitTool.createFakeMySqlConnect(),
          OperateUserSql.addSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
  }
  |> Obj.magic;