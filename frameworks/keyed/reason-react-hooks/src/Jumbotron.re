open Util;

[@react.component]
let make = (~sender) => {
  <div className="jumbotron">
    <div className="row">
      <div className="col-md-6">
        <h1> {ReasonReact.string("ReasonReact Hooks keyed")} </h1>
      </div>
      <div className="col-md-6">
        <div className="row">
          <Button id="run" title="Create 1,000 rows" cb={sender(RUN)} />
          <Button
            id="runlots"
            title="Create 10,000 rows"
            cb={sender(RUNLOTS)}
          />
          <Button id="add" title="Append 1,000 rows" cb={sender(ADD)} />
          <Button
            id="update"
            title="Update every 10th row"
            cb={sender(UPDATEEVERYTENTH)}
          />
          <Button id="clear" title="Clear" cb={sender(CLEAR)} />
          <Button id="swaprows" title="Swap Rows" cb={sender(SWAPROWS)} />
        </div>
      </div>
    </div>
  </div>;
};
let make = React.memo(make);