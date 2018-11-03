let updateSql = "UPDATE user SET name='mickey' WHERE id=:id;";

let addSql = "INSERT INTO user(name, sex, intro) VALUES(:name,:sex,'this is something');";

let deleteSql = "delete from user WHERE id=:id;";

let selectSql = "select * from user;";