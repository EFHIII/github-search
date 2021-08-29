'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Result$GithubSearch = require("./Result.bs.js");
var Matches$GithubSearch = require("./Matches.bs.js");
var KeyEvent$GithubSearch = require("./KeyEvent.bs.js");

var initialState_results = [];

var initialState = {
  results: initialState_results,
  selected: "",
  query: ""
};

function htmlResults(setState, selected, results, query) {
  var selected$1 = Belt_Array.some(results, (function (data) {
          return data.id === selected;
        })) ? selected : "";
  return Belt_Array.mapWithIndex(results, (function (index, data) {
                var a = String(data.stargazerCount);
                var number = a.split("");
                var length = number.length;
                var match = data.description;
                return React.createElement("a", {
                            className: "repoLink",
                            id: data.id,
                            href: data.url,
                            target: "_blank",
                            onMouseOver: (function (param) {
                                return Curry._1(setState, (function (param) {
                                              return {
                                                      results: results,
                                                      selected: data.id,
                                                      query: query
                                                    };
                                            }));
                              })
                          }, React.createElement("div", {
                                className: data.id === selected$1 || selected$1 === "" && index === 0 ? "container selected" : "container"
                              }, React.createElement("div", {
                                    className: "containerTitle"
                                  }, React.createElement("span", {
                                        className: "repoTitle"
                                      }, React.createElement("img", {
                                            className: "repoAvatar",
                                            src: data.avatarUrl
                                          }), React.createElement("span", undefined), Matches$GithubSearch.getMatches(data.nameWithOwner, query)), React.createElement("i", {
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
                                      }, match !== undefined ? Matches$GithubSearch.getMatches(match, query) : ""))));
              }));
}

function searchGitHub(selected, callback, $$event) {
  var query = $$String.lowercase_ascii($$event.target.value);
  Result$GithubSearch.getNResults("repos.json", query, callback, selected, 10);
  return /* () */0;
}

function Search(Props) {
  var match = React.useState((function () {
          return initialState;
        }));
  var setState = match[1];
  var state = match[0];
  var partial_arg = state.selected;
  return React.createElement("div", {
              onKeyDown: (function (param) {
                  return KeyEvent$GithubSearch.keydown(setState, param);
                })
            }, React.createElement("input", {
                  className: "searchBar",
                  autoComplete: "off",
                  name: "name",
                  placeholder: "Search GitHub...",
                  type: "text",
                  onChange: (function (param) {
                      return searchGitHub(partial_arg, setState, param);
                    })
                }), React.createElement("div", {
                  id: "results"
                }, htmlResults(setState, state.selected, state.results, state.query)));
}

var make = Search;

exports.initialState = initialState;
exports.htmlResults = htmlResults;
exports.searchGitHub = searchGitHub;
exports.make = make;
/* react Not a pure module */
