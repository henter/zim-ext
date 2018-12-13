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
 * CompiledRoutes are returned by the RouteCompiler class.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
class CompiledRoute
{
    protected variables;
    protected tokens;
    protected staticPrefix;
    protected regex;
    protected pathVariables;
    /**
     * @param string      $staticPrefix  The static prefix of the compiled route
     * @param string      $regex         The regular expression to use to match this route
     * @param array       $tokens        An array of tokens to use to generate URL for this route
     * @param array       $pathVariables An array of path variables
     * @param array       $variables     An array of variables (variables defined in the path and in the host patterns)
     */
    public function __construct(string staticPrefix, string regex, array tokens, array pathVariables, array variables = []) -> void
    {
        let this->staticPrefix = staticPrefix;
        let this->regex = regex;
        let this->tokens = tokens;
        let this->pathVariables = pathVariables;
        let this->variables = variables;
    }
    
    /**
     * Returns the static prefix.
     *
     * @return string The static prefix
     */
    public function getStaticPrefix() -> string
    {
        return this->staticPrefix;
    }
    
    /**
     * Returns the regex.
     *
     * @return string The regex
     */
    public function getRegex() -> string
    {
        return this->regex;
    }
    
    /**
     * Returns the tokens.
     *
     * @return array The tokens
     */
    public function getTokens() -> array
    {
        return this->tokens;
    }
    
    /**
     * Returns the variables.
     *
     * @return array The variables
     */
    public function getVariables() -> array
    {
        return this->variables;
    }
    
    /**
     * Returns the path variables.
     *
     * @return array The variables
     */
    public function getPathVariables() -> array
    {
        return this->pathVariables;
    }

}