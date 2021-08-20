type match = {
  starting: int,
  ending: int,
};

let rec recStyleMatches = (text, query) => {
  /*replace spaces with &nbsp; to avoid problems*/
  let text = text |> Js.String.split(" ") |> Js.Array.joinWith({j|\xa0|j});

  /*get the starting & ending index of the next match*/
  let index =
    Js.String.split(" ", query)
    ->Belt.Array.reduce([||], (a, b) =>
        b == "" ? a : Array.concat([a, [|b|]])
      )
    ->Belt.Array.reduce(
        {starting: (-1), ending: (-1)},
        (acc, qry) => {
          let qryStarting =
            Js.String.indexOf(qry, text->String.lowercase_ascii);
          switch (acc.starting, qryStarting) {
          | (a, b) when a < 0 => {
              starting: b,
              ending: b + String.length(qry),
            }
          | (_, b) when b < 0 => acc
          | (a, b) =>
            min(a, b) == a
              ? acc : {starting: b, ending: b + String.length(qry)}
          };
        },
      );

  if (index.starting < 0) {
    [|text|];
  } else {
    Belt.Array.concat(
      [|
        text->Js.String.slice(~from=0, ~to_=index.starting),
        text->Js.String.slice(~from=index.starting, ~to_=index.ending),
      |],
      recStyleMatches(text->Js.String.sliceToEnd(~from=index.ending), query),
    );
  };
};

/*wraps all matching text in a span with the class "match"*/
let styleMatches = (text, query) => {
  recStyleMatches(text, query)
  ->Belt.Array.mapWithIndex((i, a) =>
      if (i mod 2 == 0) {
        React.string(a);
      } else {
        <span className="match"> {React.string(a)} </span>;
      }
    );
};
