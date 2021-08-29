let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  body {
    background-color: rgb(224, 226, 229);
    display: flex;
    flex-direction: column;
    align-items: center;
  }
  .container {
    margin: 12px 0px;
    box-shadow: 0px 4px 16px rgb(200, 200, 200);
    width: min(100%, 1000px);
    border-radius: 12px;
    font-family: sans-serif;
  }
  .containerTitle {
    background-color: rgb(242, 243, 245);
    border-radius: 12px 12px 0px 0px;
    padding: 12px;
    font-weight: bold;
  }
  .containerContent {
    background-color: white;
    padding: 16px;
    border-radius: 0px 0px 12px 12px;
  }

  .selected {
    border-style: solid;
    border-color: skyblue;
    position: relative;
    left: -3px;
    top: -3px;
    margin-bottom: -6px;
  }

  #results:last-child{
    margin-bottom: 12px;
  }

  .searchBar {
    padding: 10px;
    font-size:17px;
    border:1px solid grey;
    width:calc(100% - 22px);
    background:rgb(242,243,244);
  }

  .repoAvatar {
    height:1.5em;
    vertical-align:middle;
    margin-right:0.5em;
  }
  .description {
    display:table;
  }
  .repoLink {
    color:black;
    text-decoration:none;
  }

  .repoLink .containerTitle {
    color:blue;
  }

  .stargazers {
    color:black;
    float:right;
  }
  .updatedDate {
    color:black;
    font-weight: normal;
  }

  .match {
    color: black;
  }

  .match:nth-child(2n) {
    color: red;
    text-decoration: underline;
  }
|j};
