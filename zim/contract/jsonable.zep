/**
 * File RequestInterface.php
 * @henter
 * Time: 2018-11-24 19:52
 *
 */
namespace Zim\Contract;

interface Jsonable
{
    public function toJson(int options = 0) -> string;
}