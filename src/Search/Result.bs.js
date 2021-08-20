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

function repoContainsWords(item, query) {
  return Belt_Array.reduce(Belt_Array.map($$String.lowercase_ascii(query).split(" "), (function (word) {
                    return repoContainsWord(item, word);
                  })), false, (function (prim, prim$1) {
                if (prim) {
                  return true;
                } else {
                  return prim$1;
                }
              }));
}

function filterResults(results, query) {
  return Belt_Array.slice(Belt_Array.reduce(results, [], (function (a, b) {
                    if (repoContainsWords(b, query)) {
                      return Belt_Array.concat(a, [b]);
                    } else {
                      return a;
                    }
                  })), 0, 10);
}

function getResults(url, query, pretty, callback) {
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
                                  return Curry._2(pretty, filterResults(a, query), query);
                                })));
              }));
}

var $$Option = /* alias */0;

exports.$$Option = $$Option;
exports.decodeResults = decodeResults;
exports.repoContainsWord = repoContainsWord;
exports.repoContainsWords = repoContainsWords;
exports.filterResults = filterResults;
exports.getResults = getResults;
/* No side effect */
