let createNoDataBaseConnect = () =>
  MySql2.Connection.connect(
    ~host="127.0.0.1",
    ~user="root",
    ~password="asd",
    ~port=3306,
    (),
  );

let createFakeMySqlConnect = () =>
  MySql2.Connection.connect(
    ~host="127.0.0.1",
    ~user="root",
    ~password="asd",
    ~database="graphql_test",
    ~port=3306,
    (),
  );

let _getDropDatabaseSql = () => "DROP DATABASE IF EXISTS graphql_test;";

let _getCreateTestDatabaseSql = () => "CREATE DATABASE graphql_test;";

let _getUseGraphqlTest = () => "use graphql_test;";

let initMysql = () => {
  PromiseUtils.await(
    MysqlCommon.handleSql(
      createNoDataBaseConnect(),
      _getDropDatabaseSql(),
      None,
    ),
  );

  PromiseUtils.await(
    MysqlCommon.handleSql(
      createNoDataBaseConnect(),
      _getCreateTestDatabaseSql(),
      None,
    ),
  );

  PromiseUtils.await(
    MysqlCommon.handleSql(
      createFakeMySqlConnect(),
      _getUseGraphqlTest(),
      None,
    ),
  );
};