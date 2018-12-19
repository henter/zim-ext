/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Routing;

/**
 * RouteCompiler compiles Route instances to CompiledRoute instances.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 */
class RouteCompiler
{
    const REGEX_PATTERN_START = "#^\{\w+\}#";
    const REGEX_PATTERN = "#\{\w+\}#";
    const REGEX_UTF8 = "/[\x80-\xFF]/";
    const REGEX_UTF8_FULL = "/[\x80-\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\{CLMNPSZ]|x\{[A-Fa-f0-9]{3})/";
    //"//for ide highlight issue

    const REGEX_DELIMITER = "#";
    /**
     * This string defines the characters that are automatically considered separators in front of
     * optional placeholders (with default and no static text following). Such a single separator
     * can be left out together with the optional placeholder from matching and generating URLs.
     */
    const SEPARATORS = "/,;.:-_~+*=@|";
    /**
     * The maximum supported length of a PCRE subpattern name
     * http://pcre.org/current/doc/html/pcre2pattern.html#SEC16.
     *
     * @internal
     */
    const VARIABLE_MAXIMUM_LENGTH = 32;
    /**
     * {@inheritdoc}
     *
     * @throws \InvalidArgumentException if a path variable is named _fragment
     * @throws \LogicException           if a variable is referenced more than once
     * @throws \DomainException          if a variable name starts with a digit or if it is too long to be successfully used as
     *                                   a PCRE subpattern
     */
    public static function compile(<Route> route)
    {
        var variables, path, result, pathVariables;
    
        let variables = [];
        let path = route->getPath();
        let result = self::compilePattern(route, path);

        let pathVariables = result["variables"];
        let variables = array_merge(variables, pathVariables);
        return new CompiledRoute(
            result["staticPrefix"],
            result["regex"],
            result["tokens"],
            pathVariables,
            array_unique(variables)
        );
    }
    
    protected static function compilePattern(<Route> route, pattern)
    {
        var tokens, variables, matches, pos, defaultSeparator, useUtf8, needsUtf8, match, varName, precedingText, precedingChar, isSeparator, regexp, followingPattern, nextSeparator, firstOptional, i, token;
    
        let tokens = [];
        let variables = [];
        let matches = [];
        let pos = 0;
        let defaultSeparator = "/";
        let useUtf8 = preg_match("//u", pattern);
        let needsUtf8 = route->getOption("utf8");
        if !needsUtf8 && useUtf8 && preg_match(self::REGEX_UTF8, pattern) {
            throw new \LogicException(sprintf("Cannot use UTF-8 route patterns without setting the \"utf8\" option for route \"%s\".", route->getPath()));
        }
        if !useUtf8 && needsUtf8 {
            throw new \LogicException(sprintf("Cannot mix UTF-8 requirements with non-UTF-8 pattern \"%s\".", pattern));
        }
        // Match all variables enclosed in "{}" and iterate over them. But we only want to match the innermost variable
        // in case of nested "{}", e.g. {foo{bar}}. This in ensured because \w does not match "{" or "}" itself.
        preg_match_all(self::REGEX_PATTERN, pattern, matches, PREG_SET_ORDER | PREG_OFFSET_CAPTURE);
        for match in matches {
            let varName = substr(match[0][0], 1, -1);
            // get all static text preceding the current variable
            let precedingText = substr(pattern, pos, match[0][1] - pos);
            let pos = match[0][1] + strlen(match[0][0]);
            if strlen(precedingText) == 0 {
                let precedingChar = "";
            } elseif useUtf8 {
                preg_match("/.$/u", precedingText, precedingChar);
                let precedingChar = precedingChar[0];
            } else {
                let precedingChar = substr(precedingText, -1);
            }
            let isSeparator = "" !== precedingChar && false !== strpos(self::SEPARATORS, precedingChar);
            // A PCRE subpattern name must start with a non-digit. Also a PHP variable cannot start with a digit so the
            // variable would not be usable as a Controller action argument.
            if preg_match("/^\d/", varName) {
                throw new \DomainException(sprintf("Variable name \"%s\" cannot start with a digit in route pattern \"%s\". Please use a different name.", varName, pattern));
            }
            if in_array(varName, variables) {
                throw new \LogicException(sprintf("Route pattern \"%s\" cannot reference variable name \"%s\" more than once.", pattern, varName));
            }
            if strlen(varName) > self::VARIABLE_MAXIMUM_LENGTH {
                throw new \DomainException(sprintf("Variable name \"%s\" cannot be longer than %s characters in route pattern \"%s\". Please use a shorter name.", varName, self::VARIABLE_MAXIMUM_LENGTH, pattern));
            }
            if isSeparator && precedingText !== precedingChar {
                let tokens[] = ["text", substr(precedingText, 0, -strlen(precedingChar))];
            } elseif !isSeparator && strlen(precedingText) > 0 {
                let tokens[] = ["text", precedingText];
            }
            let regexp = route->getRequirement(varName);
            if regexp === null {
                let followingPattern = (string) substr(pattern, pos);
                let nextSeparator = self::findNextSeparator(followingPattern, useUtf8);
                let regexp = sprintf(
                    "[^%s%s]+",
                    preg_quote(defaultSeparator, self::REGEX_DELIMITER),
                    defaultSeparator !== nextSeparator && nextSeparator !== "" ? preg_quote(nextSeparator, self::REGEX_DELIMITER) : ""
                    );
                if nextSeparator !== "" &&
                    !preg_match(self::REGEX_PATTERN_START, followingPattern) ||
                    followingPattern === "" {
                    let regexp .= "+";
                }
            } else {
                if !preg_match("//u", regexp) {
                    let useUtf8 = false;
                } elseif !needsUtf8 && preg_match(self::REGEX_UTF8_FULL, regexp) {
                    throw new \LogicException(sprintf("Cannot use UTF-8 route requirements without setting the \"utf8\" option for variable \"%s\" in pattern \"%s\".", varName, pattern));
                }
                if !useUtf8 && needsUtf8 {
                    throw new \LogicException(sprintf("Cannot mix UTF-8 requirement with non-UTF-8 charset for variable \"%s\" in pattern \"%s\".", varName, pattern));
                }
                let regexp = self::transformCapturingGroupsToNonCapturings(regexp);
            }
            let tokens[] = ["variable", isSeparator ? precedingChar : "", regexp, varName];
            let variables[] = varName;
        }
        if pos < strlen(pattern) {
            let tokens[] = ["text", substr(pattern, pos)];
        }
        // find the first optional token
        let firstOptional = PHP_INT_MAX;
        let i = 0;

        //use aa instead of direct range. seems zephir bug ? TODO
        var aa;
        let aa = range(count(tokens) - 1, 0);
        for i in aa {
            let token = tokens[i];
            if token[0] === "variable" && route->hasDefault(token[3]) {
                let firstOptional = i;
            } else {
                break;
            }
        }
        // compute the matching regexp
        let regexp = "";
        let i = 0;
        for i in range(0, count(tokens) - 1) {
            let regexp .= self::computeRegexp(tokens, i, firstOptional);
        }
        let regexp = self::REGEX_DELIMITER . "^" . regexp . "$" . self::REGEX_DELIMITER . "sD";
        // enable Utf8 matching if really required
        if needsUtf8 {
            let regexp .= "u";
            let i = 0;
            for i in range(0, count(tokens) - 1) {
                if tokens[i][0] === "variable" {
                    let tokens[i][] = true;
                }
            }
        }
        return [
            "staticPrefix" : self::determineStaticPrefix(route, tokens),
            "regex" : regexp,
            "tokens" : array_reverse(tokens),
            "variables" : variables
        ];
    }
    
    /**
     * Determines the longest static prefix possible for a route.
     */
    protected static function determineStaticPrefix(<Route> route, array tokens)
    {
        if tokens[0][0] !== "text" {
            return  route->hasDefault(tokens[0][3]) || tokens[0][1] === "/" ? "" : tokens[0][1];
        }

        var prefix;
        let prefix = tokens[0][1];
        if isset tokens[1][1] && tokens[1][1] !== "/" && route->hasDefault(tokens[1][3]) === false {
            let prefix .= tokens[1][1];
        }
        return prefix;
    }
    
    /**
     * Returns the next static character in the Route pattern that will serve as a separator (or the empty string when none available).
     */
    protected static function findNextSeparator(string pattern, bool useUtf8) -> string
    {
        if pattern == "" {
            // return empty string if pattern is empty or false (false which can be returned by substr)
            return "";
        }
        // first remove all placeholders from the pattern so we can find the next real static character
        let pattern = preg_replace(self::REGEX_PATTERN, "", pattern);
        if pattern === "" {
            return "";
        }
        if useUtf8 {
            var m;
            preg_match("/^./u", pattern, m);
            return strpos(self::SEPARATORS, m[0]) !== false ? m[0] : "";
        }

        var first;
        let first = self::at(pattern, 0);
        return strpos(self::SEPARATORS, first) !== false ? first : "";
    }
    
    /**
     * Computes the regexp used to match a specific token. It can be static text or a subpattern.
     *
     * @param array $tokens        The route tokens
     * @param int   $index         The index of the current token
     * @param int   $firstOptional The index of the first optional token
     *
     * @return string The regexp pattern for a single token
     */
    protected static function computeRegexp(array tokens, int index, int firstOptional) -> string
    {
        var token, regexp, nbTokens;

        let token = tokens[index];

        if token[0] === "text" {
            return preg_quote(token[1], self::REGEX_DELIMITER);
        } else {
            // Variable tokens
            if 0 === index && 0 === firstOptional {
                // When the only token is an optional variable token, the separator is required
                return sprintf("%s(?P<%s>%s)?", preg_quote(token[1], self::REGEX_DELIMITER), token[3], token[2]);
            } else {
                let regexp = sprintf("%s(?P<%s>%s)", preg_quote(token[1], self::REGEX_DELIMITER), token[3], token[2]);
                if index >= firstOptional {
                    // Enclose each optional token in a subpattern to make it optional.
                    // "?:" means it is non-capturing, i.e. the portion of the subject string that
                    // matched the optional subpattern is not passed back.
                    let regexp = "(?:".regexp;
                    let nbTokens = count(tokens);
                    if nbTokens - 1 == index {
                        // Close the optional subpatterns
                        let regexp .= str_repeat(")?", nbTokens - firstOptional - ( 0 === firstOptional ? 1 : 0));
                    }
                }
                return regexp;
            }
        }
        return "";
    }

    protected static function transformCapturingGroupsToNonCapturings(string regexp)
    {
        int i;
        let i = -1;
        while i < strlen(regexp) - 1 {
            let i++;
            if self::at(regexp, i) === "\\" {
                let i++;
                continue;
            }
            if self::at(regexp, i) !== "(" || !self::at(regexp, i + 2) {
                continue;
            }
            let i++;
            if self::at(regexp, i) === "*" || self::at(regexp, i) == "?" {
                let i++;
                continue;
            }
            let regexp = substr_replace(regexp, "?:", i, 0);
            let i++;
        }
        return regexp;
    }

    protected static function at(var s, int i) -> string {
        if typeof s == "array" {
            return s[i];
        }
        return substr(s, i, 1);
    }


}