/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Debug;

/**
 * ExceptionHandler converts an exception to a Response object.
 *
 * It is mostly useful in debug mode to replace the default PHP/XDebug
 * output with something prettier and more useful.
 *
 * As this class is mainly used during Kernel boot, where nothing is yet
 * available, the Response content is always HTML.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Nicolas Grekas <p@tchwork.com>
 */
class ExceptionHandler
{
    protected debug;
    protected charset;
    protected fileLinkFormat;
    public function __construct(bool debug = true, fileLinkFormat = null) -> void
    {
        let this->debug = debug;
        let this->charset =  ini_get("default_charset") ? ini_get("default_charset") : "UTF-8";
        let this->fileLinkFormat = fileLinkFormat;
    }
    
    /**
     * Registers the exception handler.
     *
     * @param bool        $debug          Enable/disable debug mode, where the stack trace is displayed
     * @param string|null $fileLinkFormat The IDE link template
     *
     * @return static
     */
    public static function register(bool debug = true, fileLinkFormat = null) -> <ExceptionHandler>
    {
        var handler;
    
        let handler = new static(debug, fileLinkFormat);
        set_exception_handler([handler, "handle"]);
        return handler;
    }
    
    /**
     * Sends a response for the given Exception.
     *
     * To be as fail-safe as possible, the exception is first handled
     * by our simple exception handler, then by the user exception handler.
     * The latter takes precedence and any output from the former is cancelled,
     * if and only if nothing bad happens in this handling path.
     */
    public function handle(<Exception> exception) -> void
    {
        this->sendPhpResponse(exception);
    }
    
    /**
     * Sends the error associated with the given Exception as a plain PHP response.
     *
     * This method uses plain PHP functions like header() and echo to output
     * the response.
     *
     * @param \Exception|FlattenException $exception An \Exception or FlattenException instance
     */
    public function sendPhpResponse(exception) -> void
    {
        var name, value;
    
        if !(exception instanceof FlattenException) {
            let exception =  FlattenException::create(exception);
        }
        if !(headers_sent()) {
            header(sprintf("HTTP/1.0 %s", exception->getStatusCode()));
            for name, value in exception->getHeaders() {
                header(name . ": " . value, false);
            }
            header("Content-Type: text/html; charset=" . this->charset);
        }
        echo this->decorate(this->getContent(exception), this->getStylesheet());
    }
    
    /**
     * @param FlattenException $exception
     * @return string
     */
    public function getContent(<FlattenException> exception) -> string
    {
        var title, content, count, total, position, e, ind, classs, message, trace;
    
        if 404 {
            let title = "Sorry, the page you are looking for could not be found.";
        } else {
            let title = "Whoops, looks like something went wrong.";
        }
        if !(this->debug) {
            return "                <div class=\"container\">\n                    <h1>{title}</h1>\n                </div>";
        }
        let content = "";
        try {
            let count =  count(exception->getAllPrevious());
            let total =  count + 1;
            for position, e in exception->toArray() {
                let ind =  count - position + 1;
                let classs =  this->formatClass(e["class"]);
                let message =  nl2br(this->escapeHtml(e["message"]));
                let content .= sprintf("                    <div class=\"trace trace-as-html\">
                        <table class=\"trace-details\">
                            <thead class=\"trace-head\"><tr><th>
                                <h3 class=\"trace-class\">
                                    <span class=\"text-muted\">(%d/%d)</span>
                                    <span class=\"exception_title\">%s</span>
                                </h3>
                                <p class=\"break-long-words trace-message\">%s</p>
                            </th></tr></thead>
                            <tbody>", ind, total, classs, message);
                for trace in e["trace"] {
                    let content .= "<tr><td>";
                    if trace["function"] {
                        let content .= sprintf("at <span class=\"trace-class\">%s</span><span class=\"trace-type\">%s</span><span class=\"trace-method\">%s</span>(<span class=\"trace-arguments\">%s</span>)", this->formatClass(trace["class"]), trace["type"], trace["function"], this->formatArgs(trace["args"]));
                    }
                    if isset trace["file"] && isset trace["line"] {
                        let content .= this->formatPath(trace["file"], trace["line"]);
                    }
                    let content .= "</td></tr>
";
                }
                let content .= "</tbody>
</table>
</div>
";
            }
        } catch \Exception, e {
            // something nasty happened and we cannot throw an exception anymore
            if this->debug {
                let e =  FlattenException::create(e);
                let title =  sprintf("Exception thrown when handling an exception (%s: %s)", e->getClass(), this->escapeHtml(e->getMessage()));
            } else {
                let title = "Whoops, looks like something went wrong.";
            }
        }
        return "            <div class=\"exception-summary\">\n                <div class=\"container\">\n                    <div class=\"exception-message-wrapper\">\n                        <h1 class=\"break-long-words exception-message\">{title}</h1>\n                        <div class=\"exception-illustration hidden-xs-down\">Zim v1.0.0</div>\n                    </div>\n                </div>\n            </div>\n\n            <div class=\"container\">\n                {content}\n            </div>";
    }
    
    /**
     * Gets the stylesheet associated with the given exception.
     *
     * @return string The stylesheet as a string
     */
    public function getStylesheet() -> string
    {
        return "            body { background-color: #F9F9F9; color: #222; font: 14px/1.4 Helvetica, Arial, sans-serif; margin: 0; padding-bottom: 45px; }

            a { cursor: pointer; text-decoration: none; }
            a:hover { text-decoration: underline; }
            abbr[title] { border-bottom: none; cursor: help; text-decoration: none; }

            code, pre { font: 13px/1.5 Consolas, Monaco, Menlo, \"Ubuntu Mono\", \"Liberation Mono\", monospace; }

            table, tr, th, td { background: #FFF; border-collapse: collapse; vertical-align: top; }
            table { background: #FFF; border: 1px solid #E0E0E0; box-shadow: 0px 0px 1px rgba(128, 128, 128, .2); margin: 1em 0; width: 100%; }
            table th, table td { border: solid #E0E0E0; border-width: 1px 0; padding: 8px 10px; }
            table th { background-color: #E0E0E0; font-weight: bold; text-align: left; }

            .hidden-xs-down { display: none; }
            .block { display: block; }
            .break-long-words { -ms-word-break: break-all; word-break: break-all; word-break: break-word; -webkit-hyphens: auto; -moz-hyphens: auto; hyphens: auto; }
            .text-muted { color: #999; }

            .container { max-width: 1024px; margin: 0 auto; padding: 0 15px; }
            .container::after { content: \"\"; display: table; clear: both; }

            .exception-summary { background: #B0413E; border-bottom: 2px solid rgba(0, 0, 0, 0.1); border-top: 1px solid rgba(0, 0, 0, .3); flex: 0 0 auto; margin-bottom: 30px; }

            .exception-message-wrapper { display: flex; align-items: center; min-height: 70px; }
            .exception-message { flex-grow: 1; padding: 30px 0; }
            .exception-message, .exception-message a { color: #FFF; font-size: 21px; font-weight: 400; margin: 0; }
            .exception-message.long { font-size: 18px; }
            .exception-message a { border-bottom: 1px solid rgba(255, 255, 255, 0.5); font-size: inherit; text-decoration: none; }
            .exception-message a:hover { border-bottom-color: #ffffff; }

            .exception-illustration { flex-basis: 111px; flex-shrink: 0; height: 66px; margin-left: 15px; opacity: .7; color: #fff; }

            .trace + .trace { margin-top: 30px; }
            .trace-head .trace-class { color: #222; font-size: 18px; font-weight: bold; line-height: 1.3; margin: 0; position: relative; }

            .trace-message { font-size: 14px; font-weight: normal; margin: .5em 0 0; }

            .trace-file-path, .trace-file-path a { color: #222; margin-top: 3px; font-size: 13px; }
            .trace-class { color: #B0413E; }
            .trace-type { padding: 0 2px; }
            .trace-method { color: #B0413E; font-weight: bold; }
            .trace-arguments { color: #777; font-weight: normal; padding-left: 2px; }

            @media (min-width: 575px) {
                .hidden-xs-down { display: initial; }
            }";
    }
    
    protected function decorate(content, css)
    {
        return "<!DOCTYPE html>\n<html>\n    <head>\n        <meta charset=\"{this->charset}\" />\n        <meta name=\"robots\" content=\"noindex,nofollow\" />\n        <style>{css}</style>\n    </head>\n    <body>\n        {content}\n    </body>\n</html>";
    }
    
    protected function formatClass(classs)
    {
        var parts;
    
        let parts =  explode("\\", classs);
        return sprintf("<abbr title=\"%s\">%s</abbr>", classs, array_pop(parts));
    }
    
    protected function formatPath(path, line)
    {
        var file, fmt, i, f, k, tmpI1, link;

        let file =  this->escapeHtml( preg_match("#[^/\\\\]*+$#", path, file) ? file[0]  : path);
        let fmt =  this->fileLinkFormat;
        if !(fmt) {
            return sprintf("<span class=\"block trace-file-path\">in <a title=\"%s%3$s\"><strong>%s</strong>%s</a></span>", this->escapeHtml(path), file,  0 < line ? " line " . line  : "");
        }
        let f = fmt;
        let i =  strpos(f, "&", max(strrpos(f, "%f"), strrpos(f, "%l"))) ? strpos(f, "&", max(strrpos(f, "%f"), strrpos(f, "%l"))) : strlen(f);
        let fmt =  array_merge([substr(f, 0, i)], preg_split("/&([^>]++)>/", substr(f, i), -1, PREG_SPLIT_DELIM_CAPTURE));

        let i = 1;
        loop {
            if isset fmt[i] {
                break;
            }

            let i++;

            let k = fmt[i];
            if 0 === strpos(path, k) {
                let path =  substr_replace(path, fmt[i], 0, strlen(k));
                break;
            }

            let i++;
        }
        let link = strtr(fmt[0], ["%f" : path, "%l" : line]);
        return sprintf("<span class=\"block trace-file-path\">in <a href=\"%s\" title=\"Go to source\"><strong>%s</string>%s</a></span>", this->escapeHtml(link), file,  0 < line ? " line " . line  : "");
    }

    /**
     * Formats an array as a string.
     *
     * @param array $args The argument array
     *
     * @return string
     */
    protected function formatArgs(array args) -> string
    {
        var result, key, item, formattedValue;
    
        let result =  [];
        for key, item in args {
            if item[0] === "object" {
                let formattedValue =  sprintf("<em>object</em>(%s)", this->formatClass(item[1]));
            } elseif "array" === item[0] {
                let formattedValue =  sprintf("<em>array</em>(%s)",  is_array(item[1]) ? this->formatArgs(item[1])  : item[1]);
            } elseif "null" === item[0] {
                let formattedValue = "<em>null</em>";
            } elseif "boolean" === item[0] {
                let formattedValue =  "<em>" . strtolower(var_export(item[1], true)) . "</em>";
            } elseif "resource" === item[0] {
                let formattedValue = "<em>resource</em>";
            } else {
                let formattedValue =  str_replace("
", "", this->escapeHtml(var_export(item[1], true)));
            }
            let result[] = is_int(key) ? formattedValue  : sprintf("'%s' => %s", this->escapeHtml(key), formattedValue);
        }
        return implode(", ", result);
    }
    
    /**
     * HTML-encodes a string.
     */
    protected function escapeHtml(str)
    {
        return htmlspecialchars(str, ENT_COMPAT | ENT_SUBSTITUTE, this->charset);
    }

}