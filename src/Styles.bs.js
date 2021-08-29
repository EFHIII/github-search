'use strict';


var reasonReactBlue = "#48a9dc";

var style = "\n  body {\n    background-color: rgb(224, 226, 229);\n    display: flex;\n    flex-direction: column;\n    align-items: center;\n  }\n  .container {\n    margin: 12px 0px;\n    box-shadow: 0px 4px 16px rgb(200, 200, 200);\n    width: min(100%, 1000px);\n    border-radius: 12px;\n    font-family: sans-serif;\n  }\n  .containerTitle {\n    background-color: rgb(242, 243, 245);\n    border-radius: 12px 12px 0px 0px;\n    padding: 12px;\n    font-weight: bold;\n  }\n  .containerContent {\n    background-color: white;\n    padding: 16px;\n    border-radius: 0px 0px 12px 12px;\n  }\n\n  .selected {\n    border-style: solid;\n    border-color: skyblue;\n    position: relative;\n    left: -3px;\n    top: -3px;\n    margin-bottom: -6px;\n  }\n\n  #results:last-child{\n    margin-bottom: 12px;\n  }\n\n  .searchBar {\n    padding: 10px;\n    font-size:17px;\n    border:1px solid grey;\n    width:calc(100% - 22px);\n    background:rgb(242,243,244);\n  }\n\n  .repoAvatar {\n    height:1.5em;\n    vertical-align:middle;\n    margin-right:0.5em;\n  }\n  .description {\n    display:table;\n  }\n  .repoLink {\n    color:black;\n    text-decoration:none;\n  }\n\n  .repoLink .containerTitle {\n    color:blue;\n  }\n\n  .stargazers {\n    color:black;\n    float:right;\n  }\n  .updatedDate {\n    color:black;\n    font-weight: normal;\n  }\n\n  .match {\n    color: black;\n  }\n\n  .match:nth-child(2n) {\n    color: red;\n    text-decoration: underline;\n  }\n";

exports.reasonReactBlue = reasonReactBlue;
exports.style = style;
/* No side effect */
