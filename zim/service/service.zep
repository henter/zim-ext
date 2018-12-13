namespace Zim\Service;

use Zim\Zim;
abstract class Service
{
    /**
     * @var Zim
     */
    protected zim;
    /**
     * Create a new service provider instance.
     *
     * @param  Zim $zim
     * @return void
     */
    public function __construct(<Zim> zim)
    {
        let this->zim = zim;
    }
    
    //execute for every request
    public function boot() -> void
    {
    }
    
    //execute once
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
        var tmpArray40cd750bba9870f18aada2478b24840a;
    
        let tmpArray40cd750bba9870f18aada2478b24840a = [];
        return tmpArray40cd750bba9870f18aada2478b24840a;
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
        var tmpArray40cd750bba9870f18aada2478b24840a;
    
        let tmpArray40cd750bba9870f18aada2478b24840a = [];
        return tmpArray40cd750bba9870f18aada2478b24840a;
    }

}