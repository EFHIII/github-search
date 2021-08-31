/*
 https://twisty-tanker-c10.notion.site/Code-Challenge-Autosuggest-using-ReasonReact-53f37a8abf5f4c8394d8a5df900b33a9
  */

let initialState = {
  Result.results: [||],
  Result.selected: "",
  Result.query: "",
};

let bounceDelay = 500.0; //ms
let maxDescriptionLength = 256;

let htmlResults = (setState, selected, results: array(Result.result), query) => {
  let selected =
    Belt.Array.some(results, data => data.id == selected) ? selected : "";

  results->Belt.Array.mapWithIndex((index, data) => {
    <a
      id={data.id}
      href={data.url}
      className="repoLink"
      target="_blank"
      onMouseOver={_ =>
        setState(_ =>
          {Result.results, Result.selected: data.id, Result.query}
        )
      }>
      <div
        className={
                    if (data.id == selected) {
                      "container selected";
                    } else if (selected == "" && index == 0) {
                      "container selected";
                    } else {
                      "container";
                    }
                  }>
        <div className="containerTitle">
          <span className="repoTitle">
            <img src={data.owner.avatarUrl} className="repoAvatar" />
            <span />
            {Matches.getMatches(data.nameWithOwner, query)->React.array}
          </span>
          <i className="updatedDate">
            {React.string(
               " Updated on "
               ++ Js.Date.toLocaleDateString(
                    Js.Date.fromString(data.updatedAt),
                  ),
             )}
          </i>
          <span className="stargazers">
            {React.string(
               string_of_int(data.stargazerCount)
               ->(
                   a => {
                     let number = Js.String.split("", a);
                     let length = Array.length(number);
                     number->Belt.Array.reduceWithIndex("", (a, b, i) =>
                       a ++ (i < 1 || (length - i) mod 3 > 0 ? "" : ",") ++ b
                     );
                   }
                 ),
             )}
            {React.string({j|★|j})}
          </span>
        </div>
        <div className="containerContent">
          <div className="description">
            {switch (data.description) {
             | Some(description)
                 when String.length(description) > maxDescriptionLength =>
               description
               ->String.sub(0, maxDescriptionLength)
               ->Matches.getMatches(query)
               ->Belt.Array.concat([|React.string("...")|])
               ->React.array
             | Some(description) =>
               description->Matches.getMatches(query)->React.array
             | None => <i> {React.string("No description...")} </i>
             }}
          </div>
        </div>
      </div>
    </a>
  });
};

let graphQLQuery = query =>
  {j|{
"query": "query { search(first: 10, type: REPOSITORY, query: \\"|j}
  ++ query
  ++ {j|\\") { nodes { ...on Repository { id url updatedAt nameWithOwner description stargazerCount owner { avatarUrl } } } } }",
"variables": {}
}|j};

let searchGitHub = (selected, setState, event) => {
  let query = String.lowercase_ascii(ReactEvent.Form.target(event)##value);
  ignore(
    Result.getResults(
      "https://api.github.com/graphql",
      graphQLQuery(query),
      setState,
      selected,
      query,
    ),
  );
};

let rec bounce = (setBounce, selected, setState, event) =>
  setBounce(bounceTime =>
    if (Js.Date.now() -. bounceTime >= bounceDelay) {
      searchGitHub(selected, setState, event);
      bounceTime;
    } else {
      ignore(
        Js.Global.setTimeout(
          () => bounce(setBounce, selected, setState, event),
          int_of_float(bounceDelay),
        ),
      );
      bounceTime;
    }
  );

let debounce = (bounceTime, setBounce, selected, setState, event) => {
  ReactEvent.Form.persist(event);
  if (Js.Date.now() -. bounceTime > bounceDelay) {
    searchGitHub(selected, setState, event);
    ignore(
      Js.Global.setTimeout(
        () => bounce(setBounce, selected, setState, event),
        int_of_float(bounceDelay),
      ),
    );
    ();
  };
  setBounce(_ => Js.Date.now());
};

[@react.component]
let make = () => {
  let (state, setState) = React.useState(_ => initialState);
  let (bounceTime, setBounce) = React.useState(_ => 0.0);
  <div onKeyDown={KeyEvent.keydown(setState)}>
    <input
      className="searchBar"
      type_="text"
      placeholder="Search GitHub..."
      name="name"
      autoComplete="off"
      onChange={debounce(bounceTime, setBounce, state.selected, setState)}
      //prevent scrolling to input when up/down is pressed
    />
    <div id="results">
      {htmlResults(setState, state.selected, state.results, state.query)
       ->React.array}
    </div>
  </div>;
};
