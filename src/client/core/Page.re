let component = ReasonReact.statelessComponent("Page");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <AddUser />
      <DeleteUser />
      <UserList />
    </div>,
};