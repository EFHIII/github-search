module Option = Belt.Option;

type result = {
  id: string,
  url: string,
  updatedAt: Js.Date.t,
  nameWithOwner: string,
  description: string,
  stargazerCount: int,
  avatarUrl: string,
};

type state = {
  results: array(result),
  selected: string,
  query: string,
};

let decodeResults = (maxLength, json) => {
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
      switch (
        d
        ->Option.flatMap(d => Js.Dict.get(d, "description"))
        ->Option.flatMap(Js.Json.decodeString)
      ) {
      | Some(desc) when String.length(desc) > maxLength =>
        String.sub(desc, 0, maxLength) ++ "..."
      | Some(desc) => desc
      | None => ""
      },
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

let getResults = (maxLength, url, requestString, setState, selected, query) => {
  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(requestString),
        ~headers=
          Fetch.HeadersInit.make({
            "Content-type": "application/json",
            "Authorization": "bearer " ++ Secrets.gitHubAPIToken,
          }),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         Js.Json.decodeObject(json)
         ->Option.getExn
         ->Js.Dict.get("data")
         ->Option.getExn
         ->Js.Json.decodeObject
         ->Option.getExn
         ->Js.Dict.get("search")
         ->Option.getExn
         ->Js.Json.decodeObject
         ->Option.getExn
         ->Js.Dict.get("nodes")
         ->Option.getExn
         ->Js.Json.decodeArray
         |> resolve
       )
    |> then_(json => {
         switch (json) {
         | Some(a) => a |> Js.Array.map(decodeResults(maxLength)) |> resolve
         | None => [||] |> resolve
         }
       })
    |> then_(a => setState(_ => {results: a, selected, query}) |> resolve)
  );
};
