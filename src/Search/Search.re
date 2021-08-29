/*
 https://twisty-tanker-c10.notion.site/Code-Challenge-Autosuggest-using-ReasonReact-53f37a8abf5f4c8394d8a5df900b33a9
  */

let initialState = {
  Result.results: [||],
  Result.selected: "",
  Result.query: "",
};

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
            <img src={data.avatarUrl} className="repoAvatar" />
            <span />
            {Matches.getMatches(data.nameWithOwner, query)->React.array}
          </span>
          <i className="updatedDate">
            {React.string(
               " Updated on " ++ Js.Date.toLocaleDateString(data.updatedAt),
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
             | Some(a) => Matches.getMatches(a, query)->React.array
             | None => React.string("")
             }}
          </div>
        </div>
      </div>
    </a>
  });
};

let searchGitHub = (selected, callback, event) => {
  let query = String.lowercase_ascii(ReactEvent.Form.target(event)##value);
  ignore(Result.getNResults("repos.json", query, callback, selected, 10));
};

[@react.component]
let make = () => {
  let (state, setState) = React.useState(_ => initialState);
  <div onKeyDown={KeyEvent.keydown(setState)}>
    <input
      className="searchBar"
      type_="text"
      placeholder="Search GitHub..."
      name="name"
      autoComplete="off"
      onChange={searchGitHub(state.selected, setState)}
    />
    <div id="results">
      {htmlResults(setState, state.selected, state.results, state.query)
       ->React.array}
    </div>
  </div>;
};
