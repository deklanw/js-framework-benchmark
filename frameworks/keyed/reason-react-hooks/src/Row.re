open Util;

let glyph_icon =
  <span className="glyphicon glyphicon-remove" ariaHidden=true />;

[@react.component]
let make = (~sender, ~selected, ~item: item) => {
  <tr className={selected ? "danger" : ""}>
    <td className="col-md-1">
      {item.id |> string_of_int |> ReasonReact.string}
    </td>
    <td className="col-md-4">
      <a onClick={sender(SELECT(item))}>
        {item.label |> ReasonReact.string}
      </a>
    </td>
    <td className="col-md-1">
      <a onClick={sender(REMOVE(item))}> glyph_icon </a>
    </td>
    <td className="col-md-6" />
  </tr>;
};
let make = React.memo(make);