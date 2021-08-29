module Option = Belt.Option;

type result = {
  id: string,
  url: string,
  updatedAt: Js.Date.t,
  nameWithOwner: string,
  description: option(string),
  stargazerCount: int,
  avatarUrl: string,
};

type state = {
  results: array(result),
  selected: string,
  query: string,
};

let decodeResults = json => {
  let d = Js.Json.decodeObject(json);
  {
    id:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "id"))
      ->Option.flatMap(Js.Json.decodeString)
      ->Option.getExn,
    url:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "url"))
      ->Option.flatMap(Js.Json.decodeString)
      ->Option.getExn,
    updatedAt:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "updatedAt"))
      ->Option.flatMap(Js.Json.decodeString)
      ->Option.getExn
      ->Js.Date.fromString,
    nameWithOwner:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "nameWithOwner"))
      ->Option.flatMap(Js.Json.decodeString)
      ->Option.getExn,
    description:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "description"))
      ->Option.flatMap(Js.Json.decodeString),
    stargazerCount:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "stargazerCount"))
      ->Option.flatMap(Js.Json.decodeNumber)
      ->Option.getExn
      ->Belt.Float.toInt,
    avatarUrl:
      d
      ->Option.flatMap(d => Js.Dict.get(d, "owner"))
      ->Option.flatMap(Js.Json.decodeObject)
      ->Option.flatMap(d => Js.Dict.get(d, "avatarUrl"))
      ->Option.flatMap(Js.Json.decodeString)
      ->Option.getExn,
  };
};

let repoContainsWord = (item, word) => {
  switch (word, item.description) {
  | ("", _) => false
  | (_, Some(desc)) =>
    Js.String.includes(word, desc->String.lowercase_ascii)
    || Js.String.includes(word, item.nameWithOwner->String.lowercase_ascii)
  | _ => Js.String.includes(word, item.nameWithOwner->String.lowercase_ascii)
  };
};

let repoContainsWords = (query, item) => {
  Js.String.split(" ", query->String.lowercase_ascii)
  ->Belt.Array.some(repoContainsWord(item));
};

let filterNResultsMatchingQuery = (results, query, n) => {
  results
  ->Belt.Array.keep(repoContainsWords(query))
  ->Belt.Array.slice(~offset=0, ~len=n);
};

let getNResults = (url, query, callback, selected, n) => {
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Js.Json.decodeArray |> resolve)
    |> then_(json =>
         switch (json) {
         | Some(a) => a |> Js.Array.map(decodeResults) |> resolve
         | None => [||] |> resolve
         }
       )
    |> then_(a =>
         callback(_ =>
           {
             results: filterNResultsMatchingQuery(a, query, n),
             selected,
             query,
           }
         )
         |> resolve
       )
  );
};
