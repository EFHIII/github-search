/*
 https://twisty-tanker-c10.notion.site/Code-Challenge-Autosuggest-using-ReasonReact-53f37a8abf5f4c8394d8a5df900b33a9
  */

let initialResults = [||];

let htmlResults = (results: array(Result.result), query) => {
  results->Belt.Array.map(data => {
    <a href={data.url} className="repoLink" target="_blank">
      <div key={data.id} className="container">
        <div className="containerTitle">
          <span className="repoTitle">
            <img src={data.avatarUrl} className="repoAvatar" />
            {Matches.styleMatches(data.nameWithOwner, query)->React.array}
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
             | Some(a) => Matches.styleMatches(a, query)->React.array
             | None => React.string("")
             }}
          </div>
        </div>
      </div>
    </a>
  });
};

let searchGitHub = (callback, event) => {
  let query = String.lowercase_ascii(ReactEvent.Form.target(event)##value);
  ignore(Result.getResults("repos.json", query, htmlResults, callback));
};

[@react.component]
let make = _ => {
  let (results, setResults) = React.useState(_ => initialResults);

  <div>
    <input
      className="searchBar"
      type_="text"
      placeholder="Search GitHub..."
      name="name"
      autoComplete="off"
      onChange={searchGitHub(setResults)}
    />
    <div> results->React.array </div>
  </div>;
};
