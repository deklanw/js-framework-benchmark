open Util;

type main_state_t = {
  data: array(item),
  selected: option(item),
};

let exclaim = (d: item, idx) =>
  if (0 == idx mod 10) {
    {...d, label: d.label ++ " !!!"};
  } else {
    d;
  };

/*
 let exclaim_inplace = (arr: array(Util.item)) => {
   let impl = (idx, d: Util.item) =>
     if (0 == idx mod 10) {
       arr[idx] = {...d, label: d.label ++ " !!!"};
     };
   impl;
 };
 */

let myReducer = (state, action) => {
  switch (action) {
  | RUN => {...state, data: build_data(1000)}

  | RUNLOTS => {...state, data: build_data(10000)}

  | ADD => {...state, data: Belt.Array.concat(state.data, build_data(1000))}

  | UPDATEEVERYTENTH =>
    /*
     Array.iteri(exclaim_inplace(state.data), state.data);
     */
    {...state, data: Js.Array.mapi(exclaim, state.data)}

  | SELECT(i) => {...state, selected: Some(i)}

  | REMOVE(i) =>
    let isnt_item = c => !(i === c);
    switch (state.selected) {
    | Some(n) when n === i => {
        selected: None,
        data: Js.Array.filter(isnt_item, state.data),
      }
    | _ => {...state, data: Js.Array.filter(isnt_item, state.data)}
    };

  | CLEAR => {data: [||], selected: None}

  | SWAPROWS =>
    if (Belt.Array.length(state.data) > 998) {
      let newArray = Belt.Array.copy(state.data);
      let elem_1 = Belt.Array.getUnsafe(newArray, 1);
      let elem_2 = Belt.Array.getUnsafe(newArray, 998);
      Belt.Array.set(newArray, 1, elem_2);
      Belt.Array.set(newArray, 998, elem_1);
      {...state, data: newArray};
    } else {
      state;
    }
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(myReducer, {data: [||], selected: None});

  let sender = React.useCallback((message, _event) => dispatch(message));
  let is_selected =
    switch (state.selected) {
    | None => (_ => false)
    | Some(n) => ((i: item) => i === n)
    };

  <div className="container">
    <Jumbotron sender />
    <table className="table table-hover table-striped test-data">
      <tbody>
        {React.array(
           Belt.Array.map(state.data, (item: item) =>
             <Row
               key={item.id |> string_of_int}
               item
               selected={is_selected(item)}
               sender
             />
           ),
         )}
      </tbody>
    </table>
    <span className="preloadicon glyphicon glyphicon-remove" ariaHidden=true />
  </div>;
};