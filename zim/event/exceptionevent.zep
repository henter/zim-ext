/**
 * File RequestEvent.php
 * @henter
 * Time: 2018-11-25 23:15
 *
 */

namespace Zim\Event;
use Zim\Http\Request;
use Zim\Http\Response;

class ExceptionEvent
{
    /**
     * @var \Throwable
     */
    protected e;

    /**
     * @var Request
     */
    protected request;

    /**
     * @var Response
     */
    protected response;

    public function __construct(<\Throwable> e, <Request> request, <Response> response = null)
    {
        let this->e = e;
        let this->request = request;
        let this->response = response;
    }

    /**
     * @return \Throwable
     */
    public function getThrowable() -> <\Throable>
    {
        return this->e;
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
     * @return Request
     */
    public function getRequest() -> <Request>
    {
        return this->request;
    }

}
