/**
 * File Event.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */
namespace Zim\Event;

use Zim\Zim;
class Event
{
    //uncaught exception
    const EXCEPTION = "zim.exception";
    /**
     * @param $event
     * @param array $payload
     * @param bool $halt
     */
    public static function fire(event, array payload = [], bool halt = false) -> void
    {
        Zim::getInstance()->make("event")->fire(event, payload, halt);
    }
    
    /**
     * @param $event
     * @param array $payload
     */
    public static function listen(event, array payload = []) -> void
    {
        Zim::getInstance()->make("event")->listen(event, payload);
    }
    
    /**
     * @param callable $callback
     */
    public static function on(callback) -> void
    {
        Zim::getInstance()->make("event")->on(callback);
    }

}