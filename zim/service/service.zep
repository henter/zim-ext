namespace Zim\Service;

use Zim\Zim;
abstract class Service
{

    public function __construct()
    {
    }

    //your logic code here, invoked before handling request
    public function boot() -> void
    {
    }

    //only for register service, binding object to container, or other bootstraping code
    public function register() -> void
    {
    }
    
    /**
     * TODO, deferred register
     *
     * Get the services provided by the provider.
     *
     * @return array
     */
    public function provides() -> array
    {
        return [];
    }
    
    /**
     * TODO, deferred register
     *
     * Get the events that trigger this service provider to register.
     *
     * @return array
     */
    public function when() -> array
    {
        return [];
    }

}