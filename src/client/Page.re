let component = ReasonReact.statelessComponent("Page");

let make = _children => {
  ...component,
  render: _self =>
    <div> <h1> (ReasonReact.string("all users list")) </h1> <Persons /> </div>,
};