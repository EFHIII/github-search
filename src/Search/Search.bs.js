'use strict';

var React = require("react");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Result$GithubSearch = require("./Result.bs.js");
var Matches$GithubSearch = require("./Matches.bs.js");

var initialResults = [];

function htmlResults(results, query) {
  return Belt_Array.map(results, (function (data) {
                var a = String(data.stargazerCount);
                var number = a.split("");
                var length = number.length;
                var match = data.description;
                return React.createElement("a", {
                            className: "repoLink",
                            href: data.url,
                            target: "_blank"
                          }, React.createElement("div", {
                                key: data.id,
                                className: "container"
                              }, React.createElement("div", {
                                    className: "containerTitle"
                                  }, React.createElement("span", {
                                        className: "repoTitle"
                                      }, React.createElement("img", {
                                            className: "repoAvatar",
                                            src: data.avatarUrl
                                          }), Matches$GithubSearch.styleMatches(data.nameWithOwner, query)), React.createElement("i", {
                                        className: "updatedDate"
                                      }, " Updated on " + data.updatedAt.toLocaleDateString()), React.createElement("span", {
                                        className: "stargazers"
                                      }, Belt_Array.reduceWithIndex(number, "", (function (a, b, i) {
                                              return a + ((
                                                        i < 1 || (length - i | 0) % 3 > 0 ? "" : ","
                                                      ) + b);
                                            })), "★")), React.createElement("div", {
                                    className: "containerContent"
                                  }, React.createElement("div", {
                                        className: "description"
                                      }, match !== undefined ? Matches$GithubSearch.styleMatches(match, query) : ""))));
              }));
}

function searchGitHub(callback, $$event) {
  var query = $$String.lowercase_ascii($$event.target.value);
  Result$GithubSearch.getResults("repos.json", query, htmlResults, callback);
  return /* () */0;
}

function Search(Props) {
  var match = React.useState((function () {
          return initialResults;
        }));
  var setResults = match[1];
  return React.createElement("div", undefined, React.createElement("input", {
                  className: "searchBar",
                  autoComplete: "off",
                  name: "name",
                  placeholder: "Search GitHub...",
                  type: "text",
                  onChange: (function (param) {
                      return searchGitHub(setResults, param);
                    })
                }), React.createElement("div", undefined, match[0]));
}

var make = Search;

exports.initialResults = initialResults;
exports.htmlResults = htmlResults;
exports.searchGitHub = searchGitHub;
exports.make = make;
/* react Not a pure module */
