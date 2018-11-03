let _query = {|
      type User{
        id: ID!
        name: String
        address: String
      }

      type Query { users: [User]! }
    |};

let _mutation = {|
      type Mutation {
        deleteUser(id: ID!): String
        addUser(name:String!, address:String!): String
      }
|};

let getUserSchema = () => _query ++ _mutation;