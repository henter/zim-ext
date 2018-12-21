/**
 * File App.php
 * @henter
 * Time: 2018-11-24 19:29
 *
 */
namespace Zim;

use Zim\Container\Container;
use Zim\Event\Event;
use Zim\Service\LogService;
use Zim\Service\Service;
use Zim\Debug\ErrorHandler;
use Zim\Debug\ExceptionHandler;
use Zim\Event\Dispatcher;
use Zim\Routing\Router;
use Zim\Http\Request;
use Zim\Config\Config;
/**
 * Class Zim
 * @package Zim
 */
class Zim extends Container
{
    const VERSION = "Zim (1.0.0)";

    /**
     * The current globally available container (if any).
     *
     * @var static
     */
    protected static instance;

    /**
     * All of the loaded configuration files.
     *
     * @var array
     */
    protected loadedConfigs = [];
    /**
     * Indicates if the application has "booted".
     *
     * @var bool
     */
    protected booted = false;
    /**
     * The loaded services.
     *
     * @var array
     */
    protected loadedServices = [];
    /**
     * The base path of the application installation.
     *
     * /           => basePath
     * /app        => APP_PATH
     * /config
     * /vendor
     *
     * @var string
     */
    protected basePath;

    public function __construct(string path = "") -> void
    {
        let this->basePath = path;
        this->registerErrorHandling();
        this->bootstrapContainer();
        this->bootstrapConfig();
        this->registerServices();
    }

    /**
     * Set the globally available instance of the container.
     *
     * @return self
     */
    public static function getInstance() -> <Container>
    {
        if is_null(self::instance) {
            let self::instance = new static();
        }
        return self::instance;
    }

    /**
     * Bootstrap the application container.
     *
     * @return void
     */
    protected function bootstrapContainer()
    {
        let self::instance = this;
        this->instance("zim", this);
        this->instance("config", new Config());
        this->instance("event", new Dispatcher());
        this->instance("router", new Router());
        this->instance("env", this->env());
        let this->aliases = [
            "Zim\\Zim": "zim",
            "Zim\\Container\\Container" : "zim",
            "Zim\\Config\\Config" : "config",
            "Zim\\Contract\\Config" : "config",
            "Zim\\Event\\Event" : "event",
            "Zim\\Event\\Dispatcher" : "event",
            "Zim\\Contract\\Request" : "request",
            "Zim\\Http\\Request" : "request",
            "Zim\\Routing\\Router" : "router"
        ];
    }
    
    protected function bootstrapConfig() -> void
    {
        this->configure("app");
        this->configure("routes");
    }
    
    protected function registerServices() -> void
    {
        var services, service;
    
        //services from config
        let services = self::config("app.services") ?: [];
        for service in services {
            this->register(service);
        }
    }
    
    /**
     * Get the version number of the application.
     *
     * @return string
     */
    public function version() -> string
    {
        return self::VERSION;
    }
    
    /**
     * Register a service provider with the application.
     *
     * @param  \Zim\Service\Service|string $service
     */
    public function register(var service)
    {
        var name;
        if !(typeof service == "object" && service instanceof Service) {
            //let service = new {service}(this);
            let service = this->make(service);
        }
        let name = get_class(service);
        if array_key_exists(name, this->loadedServices) {
            return;
        }
        let this->loadedServices[name] = service;
        if method_exists(service, "register") {
            service->register();
        }
        if this->booted {
            this->bootService(service);
        }
    }
    
    /**
     * Boots the registered providers, for every incoming request
     */
    public function boot()
    {
        if this->booted {
            return;
        }
        var s;
        for s in this->loadedServices {
            this->bootService(s);
        }
        let this->booted = true;
    }
    
    /**
     * Boot the given service provider.
     *
     * @param  \Zim\Service\Service $service
     * @return mixed
     */
    protected function bootService(<Service> service)
    {
        if method_exists(service, "boot") {
            return this->call([service, "boot"]);
        }
        return false;
    }
    
    /**
     * Determine if the application is running in the console.
     *
     * @return bool
     */
    public function inConsole() -> bool
    {
        return php_sapi_name() === "cli" || php_sapi_name() === "phpdbg";
    }

    /**
     * @return bool
     */
    public function inExtension() -> bool
    {
        //return extension_loaded("zim");
        return true;
    }

    /**
     * Get the base path for the application.
     *
     * @param  string|null $path
     * @return string
     */
    public function basePath(path = null) -> string
    {
        if this->basePath {
            return this->basePath . ( path ? "/" . path : path);
        }
        if this->inConsole() {
            let this->basePath = getcwd();
        } else {
            let this->basePath = realpath(getcwd() . "/../");
        }
        return this->basePath(path);
    }
    
    /**
     * Load a configuration file into the application.
     *
     * @param  string $name
     * @return void
     */
    public function configure(string name)
    {
        var path;
    
        if isset this->loadedConfigs[name] {
            return;
        }
        let this->loadedConfigs[name] = true;
        let path = this->getConfigPath(name);
        if path {
            this->make("config")->set(name, require path);
        }
    }
    
    /**
     * Get the path to the given configuration file.
     *
     * If no name is provided, then we'll return the path to the config folder.
     *
     * @param  string|null $name
     * @return string
     */
    public function getConfigPath(name = null) -> string
    {
        var appConfigDir, path, appConfigPath;
    
        if !name {
            let appConfigDir = this->basePath("config") . "/";
            if file_exists(appConfigDir) {
                return appConfigDir;
            } else {
                let path = this->basePath("../config/");
                if file_exists(path) {
                    return path;
                }
            }
        } else {
            let appConfigPath = this->basePath("config") . "/" . name . ".php";
            if file_exists(appConfigPath) {
                return appConfigPath;
            } else {
                let path = this->basePath("../config/" . name . ".php");
                if file_exists(path) {
                    return path;
                }
            }
        }
        return "";
    }
    
    public function env()
    {
        return self::config("zim.env");
    }
    
    /**
     * Set the error handling for the application.
     *
     * @return void
     */
    protected function registerErrorHandling()
    {
        error_reporting(E_ALL);
        //do not handle for console
        if !this->inConsole() {
            ini_set("display_errors", 0);
            ExceptionHandler::register();
            ErrorHandler::register();
        }
    }

    /**
     * @return Dispatcher
     */
    protected function getEvent()
    {
        return this->make("event");
    }
    
    /**
     * @param       $event
     * @param array $payload
     * @param bool  $halt
     * @return mixed
     */
    public function fire(event, array payload = [], bool halt = false)
    {
        return this->getEvent()->fire(event, payload, halt);
    }
    
    /**
     * @param string $name
     * @return mixed
     */
    public static function app(var name = null)
    {
        if is_null(name) {
            return self::instance;
        }
        return self::instance->make(name);
    }
    
    /**
     * Get / set the specified configuration value.
     *
     * If an array is passed as the key, we will assume you want to set an array of values.
     *
     * @param  array|string|null $key
     * @param  mixed             $default
     * @return mixed
     */
    public static function config(key = null, deft = null)
    {
        if is_null(key) {
            return self::app("config");
        }
        if is_array(key) {
            return self::app("config")->set(key);
        }
        return self::app("config")->get(key, deft);
    }

}