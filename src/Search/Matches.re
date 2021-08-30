type match = {
  starting: int,
  ending: int,
};

let rec recGetMatches = (text, query) => {
  /*replace spaces with &nbsp; to avoid problems*/
  let text = text; //{j|\xa0|j} &nbsp;

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
      recGetMatches(text->Js.String.sliceToEnd(~from=index.ending), query),
    );
  };
};

let getMatches = (text, query) => {
  recGetMatches(text, query)
  ->Belt.Array.map(a => {<span className="match"> {React.string(a)} </span>});
};
