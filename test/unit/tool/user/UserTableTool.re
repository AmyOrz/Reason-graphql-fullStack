let _getCreateUserTableSql = () => {|
    CREATE TABLE IF NOT EXISTS `user` (
        id int(11) NOT NULL AUTO_INCREMENT,
        name varchar(255) DEFAULT NULL,
        address varchar(255) DEFAULT NULL,
        PRIMARY KEY (id)
    ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
|};

let _getInsertUserFakeDataSql = () => {|
    INSERT INTO user VALUES
    ('1', 'name1','jinniuqu'),
    ('2', 'name2','jinniuqu'),
    ('3', 'name3','jinniuqu'),
    ('4', 'name4','jinniuqu');
|};

let initUserTable = () => {
  PromiseUtils.await(
    MysqlCommon.handleSql(
      MysqlInitTool.createFakeMySqlConnect(),
      _getCreateUserTableSql(),
      None,
    ),
  );
};

let insertDataIntoUser = () => {
  PromiseUtils.await(
    MysqlCommon.handleSql(
      MysqlInitTool.createFakeMySqlConnect(),
      _getInsertUserFakeDataSql(),
      None,
    ),
  );
};