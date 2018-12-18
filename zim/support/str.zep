namespace Zim\Support;

class Str
{
    /**
     * The cache of snake-cased words.
     *
     * @var array
     */
    protected static snakeCache = [];
    /**
     * The cache of camel-cased words.
     *
     * @var array
     */
    protected static camelCache = [];
    /**
     * The cache of studly-cased words.
     *
     * @var array
     */
    protected static studlyCache = [];
    /**
     * Return the remainder of a string after a given value.
     *
     * @param  string  $subject
     * @param  string  $search
     * @return string
     */
    public static function after(string subject, string search) -> string
    {
        return  search === "" ? subject : array_reverse(explode(search, subject, 2))[0];
    }
    
    /**
     * Get the portion of a string before a given value.
     *
     * @param  string  $subject
     * @param  string  $search
     * @return string
     */
    public static function before(string subject, string search) -> string
    {
        return  search === "" ? subject : explode(search, subject)[0];
    }
    
    /**
     * Convert a value to camel case.
     *
     * @param  string  $value
     * @return string
     */
    public static function camel(string value) -> string
    {
        if isset self::camelCache[value] {
            return self::camelCache[value];
        }
        let self::camelCache[value] = lcfirst(self::studly(value));
        return self::camelCache[value];
    }
    
    /**
     * Determine if a given string contains a given substring.
     *
     * @param  string  $haystack
     * @param  string|array  $needles
     * @return bool
     */
    public static function contains(string haystack, needles) -> bool
    {
        var needle, arr;
        let arr = typeof needles == "array" ? needles : [needles];

        for needle in arr {
            if needle !== "" && mb_strpos(haystack, needle) !== false {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Determine if a given string ends with a given substring.
     *
     * @param  string  $haystack
     * @param  string|array  $needles
     * @return bool
     */
    public static function endsWith(string haystack, needles) -> bool
    {
        var needle, arr;
        let arr = typeof needles == "array" ? needles : [needles];

        for needle in arr {
            if substr(haystack, -strlen(needle)) === (string) needle {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Cap a string with a single instance of a given value.
     *
     * @param  string  $value
     * @param  string  $cap
     * @return string
     */
    public static function finish(string value, string cap) -> string
    {
        var quoted;
    
        let quoted = preg_quote(cap, "/");
        return preg_replace("/(?:" . quoted . ")+$/u", "", value) . cap;
    }
    
    /**
     * Convert a string to kebab case.
     *
     * @param  string  $value
     * @return string
     */
    public static function kebab(string value) -> string
    {
        return static::snake(value, "-");
    }
    
    /**
     * Return the length of the given string.
     *
     * @param  string  $value
     * @param  string  $encoding
     * @return int
     */
    public static function length(string value, string encoding = null) -> int
    {
        if encoding {
            return mb_strlen(value, encoding);
        }
        return mb_strlen(value);
    }
    
    /**
     * Limit the number of characters in a string.
     *
     * @param  string  $value
     * @param  int     $limit
     * @param  string  $end
     * @return string
     */
    public static function limit(string value, int limit = 100, string end = "...") -> string
    {
        if mb_strwidth(value, "UTF-8") <= limit {
            return value;
        }
        return rtrim(mb_strimwidth(value, 0, limit, "", "UTF-8")) . end;
    }
    
    /**
     * Convert the given string to lower-case.
     *
     * @param  string  $value
     * @return string
     */
    public static function lower(string value) -> string
    {
        return mb_strtolower(value, "UTF-8");
    }
    
    /**
     * Limit the number of words in a string.
     *
     * @param  string  $value
     * @param  int     $words
     * @param  string  $end
     * @return string
     */
    public static function words(string value, int words = 100, string end = "...") -> string
    {
        array matches;
        preg_match("/^\\s*+(?:\\S++\\s*+){1," . words . "}/u", value, matches);
        if !(isset matches[0]) || static::length(value) === static::length(matches[0]) {
            return value;
        }
        return rtrim(matches[0]) . end;
    }
    
    /**
     * Generate a more truly "random" alpha-numeric string.
     *
     * @param  int  $length
     * @return string
     */
    public static function random(int length = 16) -> string
    {
        var stringg, len, size, bytes;
    
        let stringg = "";
        let len = strlen(stringg);
        while (len < length) {
            let size = length - len;
            let bytes = random_bytes(size);
            let stringg = stringg.substr(str_replace(["/", "+", "="], "", base64_encode(bytes)), 0, size);
            let len = strlen(stringg);
        }
        return stringg;
    }
    
    /**
     * Replace a given value in the string sequentially with an array.
     *
     * @param  string  $search
     * @param  array   $replace
     * @param  string  $subject
     * @return string
     */
    public static function replaceArray(string search, array replace, string subject) -> string
    {
        var value;
    
        for value in replace {
            let subject = static::replaceFirst(search, value, subject);
        }
        return subject;
    }
    
    /**
     * Replace the first occurrence of a given value in the string.
     *
     * @param  string  $search
     * @param  string  $replace
     * @param  string  $subject
     * @return string
     */
    public static function replaceFirst(string search, string replace, string subject) -> string
    {
        var position;
    
        if search == "" {
            return subject;
        }
        let position = strpos(subject, search);
        if position !== false {
            return substr_replace(subject, replace, position, strlen(search));
        }
        return subject;
    }
    
    /**
     * Replace the last occurrence of a given value in the string.
     *
     * @param  string  $search
     * @param  string  $replace
     * @param  string  $subject
     * @return string
     */
    public static function replaceLast(string search, string replace, string subject) -> string
    {
        var position;
    
        let position = strrpos(subject, search);
        if position !== false {
            return substr_replace(subject, replace, position, strlen(search));
        }
        return subject;
    }
    
    /**
     * Begin a string with a single instance of a given value.
     *
     * @param  string  $value
     * @param  string  $prefix
     * @return string
     */
    public static function start(string value, string prefix) -> string
    {
        var quoted;
    
        let quoted = preg_quote(prefix, "/");
        return prefix . preg_replace("/^(?:" . quoted . ")+/u", "", value);
    }
    
    /**
     * Convert the given string to upper-case.
     *
     * @param  string  $value
     * @return string
     */
    public static function upper(string value) -> string
    {
        return mb_strtoupper(value, "UTF-8");
    }
    
    /**
     * Convert the given string to title case.
     *
     * @param  string  $value
     * @return string
     */
    public static function title(string value) -> string
    {
        return mb_convert_case(value, MB_CASE_TITLE, "UTF-8");
    }
    
    /**
     * Convert a string to snake case.
     *
     * @param  string  $value
     * @param  string  $delimiter
     * @return string
     */
    public static function snake(string value, string delimiter = "_") -> string
    {
        var key, tmpValue;
    
        let key = value;
        if isset self::snakeCache[key][delimiter] {
            return self::snakeCache[key][delimiter];
        }
        if !(ctype_lower(value)) {
            let tmpValue = preg_replace("/\\s+/u", "", ucwords(value));
            let tmpValue = static::lower(preg_replace("/(.)(?=[A-Z])/u", "$1" . delimiter, tmpValue));
            let value = tmpValue;
        }
        let self::snakeCache[key][delimiter] = value;
        return self::snakeCache[key][delimiter];
    }
    
    /**
     * Determine if a given string starts with a given substring.
     *
     * @param  string  $haystack
     * @param  string|array  $needles
     * @return bool
     */
    public static function startsWith(string haystack, needles) -> bool
    {
        var needle, arr;
        let arr = typeof needles == "array" ? needles : [needles];

        for needle in arr {
            if needle !== "" && substr(haystack, 0, strlen(needle)) === (string) needle {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Convert a value to studly caps case.
     *
     * @param  string  $value
     * @return string
     */
    public static function studly(string value) -> string
    {
        var key, tmpValue;
    
        let key = value;
        if isset self::studlyCache[key] {
            return self::studlyCache[key];
        }
        let tmpValue = ucwords(str_replace(["-", "_"], " ", value));
        let value = tmpValue;

        let self::studlyCache[key] = str_replace(" ", "", value);
        return self::studlyCache[key];
    }
    
    /**
     * Returns the portion of string specified by the start and length parameters.
     *
     * @param  string  $string
     * @param  int  $start
     * @param  int|null  $length
     * @return string
     */
    public static function substr(string stringg, int start, length = null) -> string
    {
        return mb_substr(stringg, start, length, "UTF-8");
    }
    
    /**
     * Make a string's first character uppercase.
     *
     * @param  string  $string
     * @return string
     */
    public static function ucfirst(string stringg) -> string
    {
        return static::upper(static::substr(stringg, 0, 1)) . static::substr(stringg, 1);
    }

}