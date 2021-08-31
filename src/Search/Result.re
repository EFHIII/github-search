module Option = Belt.Option;

[@decco]
type owner = {avatarUrl: string};

[@decco]
type result = {
  id: string,
  url: string,
  updatedAt: string,
  nameWithOwner: string,
  description: option(string),
  stargazerCount: int,
  owner,
};

[@decco]
type search = {nodes: array(result)};

[@decco]
type data = {search};

[@decco]
type response = {data};

type state = {
  results: array(result),
  selected: string,
  query: string,
};

let getResults = (url, requestString, setState, selected, query) => {
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
    |> then_(json => response_decode(json) |> Belt.Result.getExn |> resolve)
    |> then_(a =>
         setState(_ => {results: a.data.search.nodes, selected, query})
         |> resolve
       )
  );
};
