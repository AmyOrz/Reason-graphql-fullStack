let _query = {|
      type User{
        id: ID!
        name: String
        sex: String
      }

      type Query { users: [User]! }
    |};

let _mutation = {|
      type Mutation {
        deleteUser(id: ID!): String
        addUser(name:String!, sex:String): String
      }
|};

let getUserSchema = () => _query ++ _mutation;