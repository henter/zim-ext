/**
 * File Controller.php
 * @henter
 * Time: 2018-11-24 20:07
 *
 */
namespace Zim\Http;

class Action extends Controller implements \Zim\Contract\Action
{
    protected static method = "GET";
    public function execute()
    {
        return "default action response";
    }

}