[@bs.val] external document: Js.t({..}) = "document";

type scollIntoViewProperties = {
  behavior: string,
  block: string,
};

let smoothCenterScroll = {behavior: "smooth", block: "center"};

let getResultIndex = id => {
  Js.Array.indexOf(
    document##getElementById(id),
    Js.Array.from(document##getElementById("results")##children),
  );
};

let getResultByIndex = index => {
  let length = document##getElementById("results")##children##length;
  if (length == 0) {
    "";
  } else {
    let index = (length + index) mod length;
    let result = Js.Array.from(document##getElementById("results")##children)[index];
    ignore(result##scrollIntoView(smoothCenterScroll));
    result##id;
  };
};

/*
 Arrow keys navigate between results
  */
let keydown = (setState, event) => {
  /*
   selected state identified by ID
   change selected state by getting current index,
   incrementing/decrementing (mod length), and getting the new ID
    */
  switch (ReactEvent.Keyboard.key(event)) {
  | "ArrowUp" =>
    ReactEvent.Keyboard.preventDefault(event);
    setState((state: Result.state) => {
      let currentIndex = max(0, getResultIndex(state.selected));
      (
        {
          results: state.results,
          selected: getResultByIndex(currentIndex - 1),

          query: state.query,
        }: Result.state
      );
    });
  | "ArrowDown" =>
    ReactEvent.Keyboard.preventDefault(event);
    setState(state => {
      let currentIndex = max(0, getResultIndex(state.selected));
      (
        {
          results: state.results,
          selected: getResultByIndex(currentIndex + 1),

          query: state.query,
        }: Result.state
      );
    });
  | "Enter" =>
    setState(state => {
      let id = state.selected == "" ? getResultByIndex(0) : state.selected;
      if (id != "") {
        document##getElementById(id)##click();
      };
      state;
    })
  | _ => ()
  };
};
