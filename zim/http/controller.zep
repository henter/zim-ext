/**
 * File Controller.php
 * @henter
 * Time: 2018-11-24 20:07
 *
 */
namespace Zim\Http;

use Zim\Http\Container;
use Zim\Zim;

class Controller
{
    protected static method;
    protected actions = [];

    /* inject container methods TODO */
    public function __get(string name)
    {
        if \Zim\Zim::getInstance()->has(name) {
            return \Zim\Zim::getInstance()->make(name);
        }
        return null;
    }
    
    public function app(string name)
    {
        return \Zim\Zim::getInstance()->make(name);
    }
    
    public function bind(string name, value) -> void
    {
        \Zim\Zim::getInstance()->bind(name, value);
    }
    
    /* TODO */
    /**
     * @return Request
     */
    public function getRequest()
    {
        return this->app("request");
    }
    
    /**
     * @param $uri
     * @return mixed|null
     */
    public function getActionClass(uri)
    {
        return  isset this->actions[uri] ? this->actions[uri]  : null;
    }
    
    /**
     * @param $uri
     * @return null
     */
    public function getAction(uri) -> null
    {
        var method;
    
        if method_exists(this, uri . "Action") {
            return uri . "Action";
        }
        for method in get_class_methods(this) {
            if strtolower(method) == strtolower(uri) . "action" {
                return method;
            }
        }
        return null;
    }
    
    public function getActions()
    {
        return this->actions;
    }

}