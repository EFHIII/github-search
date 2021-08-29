'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var $$String = require("bs-platform/lib/js/string.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function decodeResults(json) {
  var d = Js_json.decodeObject(json);
  return {
          id: Belt_Option.getExn(Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                          return Js_dict.get(d, "id");
                        })), Js_json.decodeString)),
          url: Belt_Option.getExn(Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                          return Js_dict.get(d, "url");
                        })), Js_json.decodeString)),
          updatedAt: new Date(Belt_Option.getExn(Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                              return Js_dict.get(d, "updatedAt");
                            })), Js_json.decodeString))),
          nameWithOwner: Belt_Option.getExn(Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                          return Js_dict.get(d, "nameWithOwner");
                        })), Js_json.decodeString)),
          description: Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                      return Js_dict.get(d, "description");
                    })), Js_json.decodeString),
          stargazerCount: Belt_Option.getExn(Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                          return Js_dict.get(d, "stargazerCount");
                        })), Js_json.decodeNumber)) | 0,
          avatarUrl: Belt_Option.getExn(Belt_Option.flatMap(Belt_Option.flatMap(Belt_Option.flatMap(Belt_Option.flatMap(d, (function (d) {
                                  return Js_dict.get(d, "owner");
                                })), Js_json.decodeObject), (function (d) {
                          return Js_dict.get(d, "avatarUrl");
                        })), Js_json.decodeString))
        };
}

function repoContainsWord(item, word) {
  var match = item.description;
  if (word === "") {
    return false;
  } else if (match !== undefined && $$String.lowercase_ascii(match).includes(word)) {
    return true;
  } else {
    return $$String.lowercase_ascii(item.nameWithOwner).includes(word);
  }
}

function repoContainsWords(query, item) {
  return Belt_Array.some($$String.lowercase_ascii(query).split(" "), (function (param) {
                return repoContainsWord(item, param);
              }));
}

function filterNResultsMatchingQuery(results, query, n) {
  return Belt_Array.slice(Belt_Array.keep(results, (function (param) {
                    return repoContainsWords(query, param);
                  })), 0, n);
}

function getNResults(url, query, callback, selected, n) {
  return fetch(url).then((function (prim) {
                      return prim.json();
                    })).then((function (json) {
                    return Promise.resolve(Js_json.decodeArray(json));
                  })).then((function (json) {
                  if (json !== undefined) {
                    return Promise.resolve(json.map(decodeResults));
                  } else {
                    return Promise.resolve([]);
                  }
                })).then((function (a) {
                return Promise.resolve(Curry._1(callback, (function (param) {
                                  return {
                                          results: filterNResultsMatchingQuery(a, query, n),
                                          selected: selected,
                                          query: query
                                        };
                                })));
              }));
}

var $$Option = /* alias */0;

exports.$$Option = $$Option;
exports.decodeResults = decodeResults;
exports.repoContainsWord = repoContainsWord;
exports.repoContainsWords = repoContainsWords;
exports.filterNResultsMatchingQuery = filterNResultsMatchingQuery;
exports.getNResults = getNResults;
/* No side effect */
