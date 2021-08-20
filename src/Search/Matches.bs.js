'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

function recStyleMatches(text, query) {
  var text$1 = text.split(" ").join("\xa0");
  var index = Belt_Array.reduce(Belt_Array.reduce(query.split(" "), [], (function (a, b) {
              if (b === "") {
                return a;
              } else {
                return $$Array.concat(/* :: */[
                            a,
                            /* :: */[
                              [b],
                              /* [] */0
                            ]
                          ]);
              }
            })), {
        starting: -1,
        ending: -1
      }, (function (acc, qry) {
          var qryStarting = $$String.lowercase_ascii(text$1).indexOf(qry);
          var match = acc.starting;
          if (match < 0) {
            return {
                    starting: qryStarting,
                    ending: qryStarting + qry.length | 0
                  };
          } else if (qryStarting < 0 || (
              match < qryStarting ? match : qryStarting
            ) === match) {
            return acc;
          } else {
            return {
                    starting: qryStarting,
                    ending: qryStarting + qry.length | 0
                  };
          }
        }));
  if (index.starting < 0) {
    return [text$1];
  } else {
    return Belt_Array.concat([
                (function (param) {
                        return (function (param$1) {
                            return text$1.slice(param, param$1);
                          });
                      })(0)(index.starting),
                (function (param) {
                        return (function (param$1) {
                            return text$1.slice(param, param$1);
                          });
                      })(index.starting)(index.ending)
              ], recStyleMatches((function (param) {
                        return text$1.slice(param);
                      })(index.ending), query));
  }
}

function styleMatches(text, query) {
  return Belt_Array.mapWithIndex(recStyleMatches(text, query), (function (i, a) {
                if (i % 2 === 0) {
                  return a;
                } else {
                  return React.createElement("span", {
                              className: "match"
                            }, a);
                }
              }));
}

exports.recStyleMatches = recStyleMatches;
exports.styleMatches = styleMatches;
/* react Not a pure module */
