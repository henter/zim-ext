/**
 * File Kernel.php
 * @henter
 * Time: 2018-11-26 16:07
 */
namespace Zim\Http;

use Zim\Event\Event;
use Zim\Event\DispatchEvent;
use Zim\Event\RequestEvent;
use Zim\Event\ResponseEvent;
use Zim\Event\TerminateEvent;
use Zim\Event\ExceptionEvent;
use Zim\Routing\Router;
use Zim\Support\Str;
use Zim\Zim;
use Zim\Contract\Arrayable;
use Zim\Contract\Jsonable;
use Zim\Http\Exception\NotFoundException;

class Kernel
{
    /**
     * @var Zim
     */
    protected zim;
    /**
     * @var Router
     */
    protected router;
    /**
     * Create a new HTTP kernel instance.
     *
     * @param  Zim    $zim
     * @param  Router $router
     * @return void
     */
    public function __construct(<Zim> zim, <Router> router)
    {
        let this->zim = zim;
        let this->router = router;
        this->bootstrapRoutes();
    }
    
    protected function bootstrapRoutes()
    {
        var configs, pattern, to;
    
        let configs = Zim::config("routes");
        //just in-case if routes.php not returned any configs as the value would be 1
        if typeof configs != "array" {
            return false;
        }
        for pattern, to in configs {
            this->router->addRoute([], pattern, to);
        }
        return true;
    }
    
    /**
     * @param Request $request
     * @return Response
     * @throws \Throwable
     */
    public function handle(<Request> request) -> <Response>
    {
        var requestEvent, resp, response, e, respEvent;
        try {
            this->zim->instance("request", request);
            this->zim->boot();
            let requestEvent = new RequestEvent(request);
            Event::fire(requestEvent);
            let resp = requestEvent->getResponse();
            if resp {
                return resp->prepare(request);
            }

            let response = this->handleRequest(request);
            let respEvent = new ResponseEvent(request, response);
            Event::fire(respEvent);
            let response = respEvent->getResponse();
        } catch \Throwable, e {
            let response = this->handleException(e, request);
        }
        return response->prepare(request);
    }

    private function handleRequest(<Request> request) {
        var response;
        try {
            let response = this->dispatchToRouter(request);
        } catch NotFoundException {
            let response = this->dispatchToDefault(request);
        }
        return response;
    }

    /**
     * Handles an exception by trying to convert it to a Response.
     *
     * @param \Throwable $e       An \Exception instance
     * @param Request    $request A Request instance
     * @return Response
     * @throws \Exception
     */
    private function handleException(<\Throwable> e, <Request> request) -> <Response>
    {
        var event, resp;
        let event = new ExceptionEvent(e, request);
        Event::fire(event, null, true);
        let resp = event->getResponse();
        if !resp {
            //seems zehpir bug, exception handler cannot catch exception in a try-catch flow
            //throw e;
            let resp = new Response(\Zim\Debug\Handler::getInstance()->getHtml(e));
        }

        return resp;
    }

    /**
     * 根据 uri 猜测 controller 类名
     * @param string $uri
     * @return string|bool
     */
    protected function guessController(string uri)
    {
        if class_exists("App\\Controller\\" . ucfirst(uri) . "Controller") {
            return ucfirst(uri);
        }

        if !defined("APP_PATH") {
            return false;
        }

        var suffix, files, file, name;
        let suffix = "Controller.php";
        let files = glob(APP_PATH . "/Controller/*" . suffix);
        for file in files {
            let name = Str::replaceLast(suffix, "", basename(file));
            if uri === strtolower(name) {
                return name;
            }
        }
        return false;
    }
    
    /**
     * default IndexController indexAction, same as yaf
     *
     * rules:
     * /            => Index@index
     * /foo         => Foo@index or Index@foo
     * /foo/bar     => Foo@bar
     *
     * @param Request $request
     * @return array
     */
    protected function getDefaultRoute(<Request> request) -> array
    {
        var segments, c, a, tmpListCA;
    
        let segments = array_filter(explode("/", trim(request->getPathInfo(), "/")));
        if !segments {
            return ["Index", "index"];
        }
        //list($c, $a) = isset($segments[1]) ? $segments : [$segments[0], 'index'];
        //zephir
        if isset segments[1] {
            let tmpListCA = segments;
            let c = tmpListCA[0];
            let a = tmpListCA[1];
        } else {
            let c = segments[0];
            let a = "index";
        }
        //如果 FooController 不存在，则尝试调度到 IndexController@fooAction
        let c = this->guessController(c);
        if !c {
            let c = "Index";
            let a = segments[0];
        }
        return [c, a];
    }
    
    /**
     * 默认路由规则
     * 即：
     *      如果存在 FooController
     *      /foo     => App\Controller\FooController::indexAction
     *      /foo/bar => App\Controller\FooController::barAction
     *      /foo/bar => App\Controller\FooController::$actions[bar]::execute
     *
     *      否则
     *      /foo     => App\Controller\IndexController::fooAction
     *      /foo/bar => App\Controller\IndexController::fooAction
     *
     * @param Request $request
     * @return Response
     * @throws \Throwable
     */
    public function dispatchToDefault(<Request> request) -> <Response>
    {
        var c, a, tmpListCA, controller, method, call, actionClass;
    
        //FooController index
        let tmpListCA = this->getDefaultRoute(request);
        let c = tmpListCA[0];
        let a = tmpListCA[1];
        /**
         * @var Controller $controller
         */
        let controller = this->zim->make("App\\Controller\\" . c . "Controller");
        //try controller action ?
        let method = controller->getAction(a);
        if method {
            let call = [controller, method];
            //mayby private method ?
            if !is_callable(call) {
                throw new NotFoundException("action not found " . call[1]);
            }
        } else {
            //try controller action class
            let actionClass = controller->getActionClass(a);
            if !actionClass || !class_exists(actionClass) {
                throw new NotFoundException("action not found");
            }
            let call = [this->zim->make(actionClass), "execute"];
        }
        return this->doDispatch(request, call);
    }
    
    /**
     * 基于路由规则匹配
     *
     * @param Request $request
     * @return Response
     */
    public function dispatchToRouter(<Request> request) -> <Response>
    {
        var route, call;
    
        let route = this->router->matchRequest(request);
        let call = route->getDefault("_callable");
        if !call {
            let call = [
                this->zim->make(route->getDefault("_controller")),
                route->getDefault("_action")
            ];
            if !is_callable(call) {
                throw new NotFoundException("action not found " . call[1]);
            }
        }
        return this->doDispatch(request, call, route->getParameters());
    }
    
    /**
     * @param Request  $request
     * @param callable $callable
     * @param array    $params
     * @return Response
     */
    protected function doDispatch(<Request> request, var call, array params = []) -> <Response>
    {
        var e, resp;

        if is_array(call) {
            request->attributes->set("callable", [get_class(call[0]), call[1]]);
        } else {
            request->attributes->set("callable", ["Closure", "Closure"]);
        }
        let e = new DispatchEvent(request);
        Event::fire(e);
        let resp = e->getResponse();
        if resp {
            return resp->prepare(request);
        }
        return this->toResponse(this->zim->call(call, params));
    }
    
    /**
     * @param mixed $resp
     * @return Response
     */
    protected function toResponse(resp)
    {
        var response;

        if typeof resp == "object" && resp instanceof Response {
            let response = resp;
        } elseif this->shouldBeJson(resp) {
            let response = new JsonResponse(resp);
        } else {
            let response = new Response(resp);
        }
        return response;
    }

    /**
     * Determine if the given content should be turned into JSON.
     *
     * @param  mixed  $content
     * @return bool
     */
    protected function shouldBeJson(var content)
    {
        return is_array(content) || (typeof content == "object" && (
            content instanceof Arrayable ||
            content instanceof Jsonable ||
            content instanceof \ArrayObject ||
            content instanceof \JsonSerializable
        ));
    }

    /**
     * will not return to fastcgi
     *
     * @param Request  $request
     * @param Response $response
     */
    public function terminate(<Request> request, <Response> response) -> void
    {
        Event::fire(new TerminateEvent(request, response));
    }

}