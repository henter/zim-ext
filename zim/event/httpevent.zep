/**
 * File RequestEvent.php
 * @henter
 * Time: 2018-11-25 23:15
 *
 */
namespace Zim\Event;

use Zim\Contract\Request;
use Zim\Contract\Response;
abstract class HttpEvent
{
    /**
     * @var Request
     */
    protected request;
    /**
     * @var Response
     */
    protected response;
    public function __construct(<Request> request, <Response> response = null) -> void
    {
        let this->request = request;
        let this->response = response;
    }
    
    /**
     * @return Response
     */
    public function getResponse() -> <Response>
    {
        return this->response;
    }
    
    /**
     * @param Response $response
     * @return $this
     */
    public function setResponse(<Response> response)
    {
        let this->response = response;
        return this;
    }

    /**
     * Returns whether a response was set.
     *
     * @return bool Whether a response was set
     */
    public function hasResponse() -> bool
    {
        return null !== this->response;
    }

    /**
     * @return Request
     */
    public function getRequest() -> <Request>
    {
        return this->request;
    }

}