/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Http;

/**
 * HTTP header utility functions.
 *
 * @author Christian Schmidt <github@chsc.dk>
 */
class HeaderUtils
{
    /**
     * This class should not be instantiated.
     */
    protected function __construct() -> void
    {
    }
    
    /**
     * Splits an HTTP header by one or more separators.
     *
     * Example:
     *
     *     HeaderUtils::split("da, en-gb;q=0.8", ",;")
     *     // => array(array('da'), array('en-gb', 'q=0.8'))
     *
     * @param string $header     HTTP header value
     * @param string $separators List of characters to split on, ordered by
     *                           precedence, e.g. ",", ";=", or ",;="
     *
     * @return array Nested array with as many levels as there are characters in
     *               $separators
     */
    public static function split(string header, string separators) -> array
    {
        var quotedSeparators, matches;
        let matches = [];
    
        let quotedSeparators =  preg_quote(separators, "/");
        preg_match_all("
            /
                (?!\\s)
                    (?:
                        # quoted-string
                        \"(?:[^\"\\\\]|\\\\.)*(?:\"|\\\\|$)
                    |
                        # token
                        [^\"" . quotedSeparators . "]+
                    )+
                (?<!\\s)
            |
                # separator
                \\s*
                (?<separator>[" . quotedSeparators . "])
                \\s*
            /x", trim(header), matches, PREG_SET_ORDER);
        return self::groupParts(matches, separators);
    }
    
    /**
     * Combines an array of arrays into one associative array.
     *
     * Each of the nested arrays should have one or two elements. The first
     * value will be used as the keys in the associative array, and the second
     * will be used as the values, or true if the nested array only contains one
     * element. Array keys are lowercased.
     *
     * Example:
     *
     *     HeaderUtils::combine(array(array("foo", "abc"), array("bar")))
     *     // => array("foo" => "abc", "bar" => true)
     */
    public static function combine(array parts)
    {
        var assoc, part, name, value;
    
        let assoc =  [];
        for part in parts {
            let name =  strtolower(part[0]);
            let value =  isset part[1] ? part[1]  : true;
            let assoc[name] = value;
        }
        return assoc;
    }
    
    /**
     * Joins an associative array into a string for use in an HTTP header.
     *
     * The key and value of each entry are joined with "=", and all entries
     * are joined with the specified separator and an additional space (for
     * readability). Values are quoted if necessary.
     *
     * Example:
     *
     *     HeaderUtils::toString(array("foo" => "abc", "bar" => true, "baz" => "a b c"), ",")
     *     // => 'foo=abc, bar, baz="a b c"'
     */
    public static function toString(array assoc, string separator)
    {
        var parts, name, value;
    
        let parts =  [];
        for name, value in assoc {
            if value === true {
                let parts[] = name;
            } else {
                let parts[] =  name . "=" . self::quote(value);
            }
        }
        return implode(separator . " ", parts);
    }
    
    /**
     * Encodes a string as a quoted string, if necessary.
     *
     * If a string contains characters not allowed by the "token" construct in
     * the HTTP specification, it is backslash-escaped and enclosed in quotes
     * to match the "quoted-string" construct.
     */
    public static function quote(string s)
    {
        if preg_match("/^[a-z0-9!#$%&'*.^_`|~-]+$/i", s) {
            return s;
        }
        return "\"" . addcslashes(s, "\"\\\"") . "\"";
    }
    
    /**
     * Decodes a quoted string.
     *
     * If passed an unquoted string that matches the "token" construct (as
     * defined in the HTTP specification), it is passed through verbatimly.
     */
    public static function unquote(string s)
    {
        return preg_replace("/\\\\(.)|\"/", "$1", s);
    }
    
    protected static function groupParts(array tmpmatches, string separators)
    {
        var separator, partSeparators, i, partMatches, match, parts, matches;
        //wtf ??
        let matches = tmpmatches;
    
        let separator = separators[0];
        let partSeparators =  substr(separators, 1);
        let i = 0;
        let partMatches =  [];
        for match in matches {
            if isset match["separator"] && match["separator"] === separator {
                let i++;
            } else {
                let partMatches[i][] = match;
            }
        }
        let parts =  [];
        if partSeparators {
            for matches in partMatches {
                let parts[] = self::groupParts(matches, partSeparators);
            }
        } else {
            for matches in partMatches {
                let parts[] = self::unquote(matches[0][0]);
            }
        }
        return parts;
    }

}