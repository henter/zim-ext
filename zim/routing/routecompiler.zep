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
        var variables, path, result, staticPrefix, pathVariables, pathParam, tokens, regex;
    
        let variables =  [];
        let path =  route->getPath();
        let result =  self::compilePattern(route, path);
        let staticPrefix = result["staticPrefix"];
        let pathVariables = result["variables"];
        for pathParam in pathVariables {
            if pathParam === "_fragment" {
                throw new \InvalidArgumentException(sprintf("Route pattern \"%s\" cannot contain \"_fragment\" as a path parameter.", route->getPath()));
            }
        }
        let variables =  array_merge(variables, pathVariables);
        let tokens = result["tokens"];
        let regex = result["regex"];
        return new CompiledRoute(staticPrefix, regex, tokens, pathVariables, array_unique(variables));
    }
    
    protected static function compilePattern(<Route> route, pattern)
    {
        var tokens, variables, matches, pos, defaultSeparator, useUtf8, needsUtf8, match, varName, precedingText, precedingChar, isSeparator, regexp, followingPattern, nextSeparator, firstOptional, i, token, nbToken, tmpArraybd8ddaaf9600b692848ab052089377c5;
    
        let tokens =  [];
        let variables =  [];
        let matches =  [];
        let pos = 0;
        let defaultSeparator = "/";
        let useUtf8 =  preg_match("//u", pattern);
        let needsUtf8 =  route->getOption("utf8");
        if !(needsUtf8) && useUtf8 && preg_match("/[\\x80-\\xFF]/", pattern) {
            throw new \LogicException(sprintf("Cannot use UTF-8 route patterns without setting the \"utf8\" option for route \"%s\".", route->getPath()));
        }
        if !(useUtf8) && needsUtf8 {
            throw new \LogicException(sprintf("Cannot mix UTF-8 requirements with non-UTF-8 pattern \"%s\".", pattern));
        }
        // Match all variables enclosed in "{}" and iterate over them. But we only want to match the innermost variable
        // in case of nested "{}", e.g. {foo{bar}}. This in ensured because \w does not match "{" or "}" itself.
        preg_match_all("#\\{\\w+\\}#", pattern, matches, PREG_SET_ORDER | PREG_OFFSET_CAPTURE);
        for match in matches {
            let varName =  substr(match[0][0], 1, -1);
            // get all static text preceding the current variable
            let precedingText =  substr(pattern, pos, match[0][1] - pos);
            let pos =  match[0][1] + strlen(match[0][0]);
            if !(strlen(precedingText)) {
                let precedingChar = "";
            } elseif useUtf8 {
                preg_match("/.$/u", precedingText, precedingChar);
                let precedingChar = precedingChar[0];
            } else {
                let precedingChar =  substr(precedingText, -1);
            }
            let isSeparator =  "" !== precedingChar && false !== strpos(self::SEPARATORS, precedingChar);
            // A PCRE subpattern name must start with a non-digit. Also a PHP variable cannot start with a digit so the
            // variable would not be usable as a Controller action argument.
            if preg_match("/^\\d/", varName) {
                throw new \DomainException(sprintf("Variable name \"%s\" cannot start with a digit in route pattern \"%s\". Please use a different name.", varName, pattern));
            }
            if in_array(varName, variables) {
                throw new \LogicException(sprintf("Route pattern \"%s\" cannot reference variable name \"%s\" more than once.", pattern, varName));
            }
            if strlen(varName) > self::VARIABLE_MAXIMUM_LENGTH {
                throw new \DomainException(sprintf("Variable name \"%s\" cannot be longer than %s characters in route pattern \"%s\". Please use a shorter name.", varName, self::VARIABLE_MAXIMUM_LENGTH, pattern));
            }
            if isSeparator && precedingText !== precedingChar {
                let tokens[] =  ["text", substr(precedingText, 0, -strlen(precedingChar))];
            } elseif !(isSeparator) && strlen(precedingText) > 0 {
                let tokens[] =  ["text", precedingText];
            }
            let regexp =  route->getRequirement(varName);
            if regexp === null {
                let followingPattern =  (string) substr(pattern, pos);
                // Find the next static character after the variable that functions as a separator. By default, this separator and '/'
                // are disallowed for the variable. This default requirement makes sure that optional variables can be matched at all
                // and that the generating-matching-combination of URLs unambiguous, i.e. the params used for generating the URL are
                // the same that will be matched. Example: new Route('/{page}.{_format}', array('_format' => 'html'))
                // If {page} would also match the separating dot, {_format} would never match as {page} will eagerly consume everything.
                // Also even if {_format} was not optional the requirement prevents that {page} matches something that was originally
                // part of {_format} when generating the URL, e.g. _format = 'mobile.html'.
                let nextSeparator =  self::findNextSeparator(followingPattern, useUtf8);
                let regexp =  sprintf("[^%s%s]+", preg_quote(defaultSeparator, self::REGEX_DELIMITER),  defaultSeparator !== nextSeparator && nextSeparator !== "" ? preg_quote(nextSeparator, self::REGEX_DELIMITER)  : "");
                if nextSeparator !== "" && !(preg_match("#^\\{\\w+\\}#", followingPattern)) || followingPattern === "" {
                    // When we have a separator, which is disallowed for the variable, we can optimize the regex with a possessive
                    // quantifier. This prevents useless backtracking of PCRE and improves performance by 20% for matching those patterns.
                    // Given the above example, there is no point in backtracking into {page} (that forbids the dot) when a dot must follow
                    // after it. This optimization cannot be applied when the next char is no real separator or when the next variable is
                    // directly adjacent, e.g. '/{x}{y}'.
                    let regexp .= "+";
                }
            } else {
                if !(preg_match("//u", regexp)) {
                    let useUtf8 =  false;
                } elseif !(needsUtf8) && preg_match("/[\\x80-\\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\\{CLMNPSZ]|x\\{[A-Fa-f0-9]{3})/", regexp) {
                    throw new \LogicException(sprintf("Cannot use UTF-8 route requirements without setting the \"utf8\" option for variable \"%s\" in pattern \"%s\".", varName, pattern));
                }
                if !(useUtf8) && needsUtf8 {
                    throw new \LogicException(sprintf("Cannot mix UTF-8 requirement with non-UTF-8 charset for variable \"%s\" in pattern \"%s\".", varName, pattern));
                }
                let regexp =  self::transformCapturingGroupsToNonCapturings(regexp);
            }
            let tokens[] =  ["variable",  isSeparator ? precedingChar  : "", regexp, varName];
            let variables[] = varName;
        }
        if pos < strlen(pattern) {
            let tokens[] =  ["text", substr(pattern, pos)];
        }
        // find the first optional token
        let firstOptional =  PHP_INT_MAX;
        let i = count(tokens) - 1;
        for i in range(count(tokens) - 1, 0) {
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
        let nbToken = count(tokens);
        for i in range(0, nbToken) {
            let regexp .= self::computeRegexp(tokens, i, firstOptional);
        }
        let regexp =  self::REGEX_DELIMITER . "^" . regexp . "$" . self::REGEX_DELIMITER . "sD";
        // enable Utf8 matching if really required
        if needsUtf8 {
            let regexp .= "u";
            let i = 0;
            let nbToken = count(tokens);
            for i in range(0, nbToken) {
                if tokens[i][0] === "variable" {
                    let tokens[i][] = true;
                }
            }
        }
        let tmpArraybd8ddaaf9600b692848ab052089377c5 = ["staticPrefix" : self::determineStaticPrefix(route, tokens), "regex" : regexp, "tokens" : array_reverse(tokens), "variables" : variables];
        return tmpArraybd8ddaaf9600b692848ab052089377c5;
    }
    
    /**
     * Determines the longest static prefix possible for a route.
     */
    protected static function determineStaticPrefix(<Route> route, array tokens)
    {
        var prefix;
    
        if tokens[0][0] !== "text" {
            return  route->hasDefault(tokens[0][3]) || tokens[0][1] === "/" ? ""  : tokens[0][1];
        }
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
        let pattern =  preg_replace("#\\{\\w+\\}#", "", pattern);
        if pattern === "" {
            return "";
        }
        var tmp_pattern;
        let tmp_pattern = pattern;
        if useUtf8 {
            preg_match("/^./u", tmp_pattern, tmp_pattern);
        }
        var ret = "";
        if strpos(self::SEPARATORS, tmp_pattern[0]) !== false {
            let ret = tmp_pattern[0];
        }
        return ret;
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

        if isset tokens[index] {
            let token = tokens[index];
        } else {
            return "";
        }
        if self::strat(token, 0) === "text" {
            // Text tokens
            return preg_quote(self::strat(token, 1), self::REGEX_DELIMITER);
        } else {
            // Variable tokens
            if 0 === index && 0 === firstOptional {
                // When the only token is an optional variable token, the separator is required
                return sprintf("%s(?P<%s>%s)?", preg_quote(token[1], self::REGEX_DELIMITER), token[3], token[2]);
            } else {
                //let regexp = sprintf("%s(?P<%s>%s)", preg_quote(token[1], self::REGEX_DELIMITER), token[3], token[2]);
                let regexp = sprintf("%s(?P<%s>%s)", preg_quote(self::strat(token, 1), self::REGEX_DELIMITER), self::strat(token, 3), self::strat(token, 2));
                if index >= firstOptional {
                    // Enclose each optional token in a subpattern to make it optional.
                    // "?:" means it is non-capturing, i.e. the portion of the subject string that
                    // matched the optional subpattern is not passed back.
                    let regexp = "(?:{regexp}";
                    let nbTokens = count(tokens);
                    if nbTokens - 1 == index {
                        // Close the optional subpatterns
                        let regexp .= str_repeat(")?", nbTokens - firstOptional - ( 0 === firstOptional ? 1  : 0));
                    }
                }
                return regexp;
            }
        }
        return "";
    }

    protected static function transformCapturingGroupsToNonCapturings(string regexp)
    {
        int i, i2;
        var s, s2;

        let i = 0;
        for i in range(0, strlen(regexp)) {
            let s = regexp[i];

            if s === "\\" {
                let i++;
                continue;
            }
            let i2 = (int)(i + 2);
            //if s !== "(" || !(isset regexp[i2]) {
            if s !== "(" || strlen(regexp[i2]) == 0 {
                continue;
            }
            let i++;
            if s === "*" || s === "?" {
                let i++;
                continue;
            }
            let regexp = substr_replace(regexp, "?:", i, 0);
            let i++;
        }
        return regexp;
    }

    protected static function strat(var s, int i) -> string {
        return substr(s, i, 1);
    }


}