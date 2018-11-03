let updateSql = "UPDATE user SET name='mickey' WHERE id=:id;";

let addSql = "INSERT INTO user(name, address) VALUES(:name,:address);";

let deleteSql = "delete from user WHERE id=:id;";

let selectSql = "select * from user;";