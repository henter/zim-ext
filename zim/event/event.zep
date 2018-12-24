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
     * @param callable $listener
     */
    public static function listen(event, callable listener) -> void
    {
        Zim::getInstance()->make("event")->listen(event, listener);
    }
    
    /**
     * @param callable $callback
     */
    public static function on(callback) -> void
    {
        Zim::getInstance()->make("event")->on(callback);
    }

}