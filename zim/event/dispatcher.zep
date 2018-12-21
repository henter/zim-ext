/**
 * File Dispatcher.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */
namespace Zim\Event;

use Zim\Container\BoundMethod;
use Zim\Zim;
class Dispatcher
{
    /**
     * The registered event listeners.
     *
     * @var array
     */
    protected listeners = [];
    /**
     * Register an event listener with the dispatcher.
     *
     * @param  string|array  $events
     * @param  mixed  $listener
     * @return void
     */
    public function listen(var events, listener)
    {
        var event;
        var arr;
        let arr = typeof events == "array" ? events : [events];
        for event in arr {
            let this->listeners[event][] = new Listener(listener);
        }
    }
    
    /**
     * sugar method to listen and callback specific event object
     *
     * @param callable $callback
     */
    public function on(callback) -> void
    {
        var r, params, eventClass;

        let params = Zim::getInstance()->reflectionParams(callback);
        if !params {
            throw new \InvalidArgumentException("event on callback parameter empty");
        }
        let eventClass = current(params)->getClass()->getName();
        this->listen(eventClass, new ListenerOn(callback));
    }
    
    /**
     * Fire an event and call the listeners.
     *
     * @param  string|object  $event
     * @param  mixed  $payload
     * @param  bool  $halt
     * @return array|null
     */
    public function fire(var event, var payload = [], bool halt = false)
    {
        var tmpListEventPayload, responses, listener, response;

        // When the given "event" is actually an object we will assume it is an event
        // object and use the class as the event name and this event itself as the
        // payload to the handler, which makes object based events quite simple.
        let tmpListEventPayload = this->parseEventAndPayload(event, payload);
        let event = tmpListEventPayload[0];
        let payload = tmpListEventPayload[1];
        let responses = [];
        for listener in this->getListeners(event) {
            let response = {listener}(event, payload);
            // If a response is returned from the listener and event halting is enabled
            // we will just return this response, and not call the rest of the event
            // listeners. Otherwise we will add the response on the response list.
            if halt && !is_null(response) {
                return response;
            }
            // If a boolean false is returned from a listener, we will stop propagating
            // the event to any further listeners down in the chain, else we keep on
            // looping through the listeners and firing every one in our sequence.
            if response === false {
                break;
            }
            let responses[] = response;
        }
        return halt ? null : responses;
    }
    
    /**
     * Parse the given event and payload and prepare them for dispatching.
     *
     * @param  mixed  $event
     * @param  mixed  $payload
     * @return array
     */
    protected function parseEventAndPayload(var event, var payload) -> array
    {
        if is_object(event) {
            return [get_class(event), event];
        }
        let payload = is_array(payload) ? payload : [payload];
        return [event, payload];
    }
    
    /**
     * Get all of the listeners for a given event name.
     *
     * @param  string  $eventName
     * @return array
     */
    public function getListeners(string eventName) -> array
    {
        var listeners;
    
        let listeners = isset this->listeners[eventName] ? this->listeners[eventName] : [];
        return  class_exists(eventName, false) ? this->addInterfaceListeners(eventName, listeners) : listeners;
    }
    
    /**
     * Add the listeners for the event's interfaces to the given array.
     *
     * @param  string  $eventName
     * @param  array  $listeners
     * @return array
     */
    protected function addInterfaceListeners(string eventName, array listeners = []) -> array
    {
        var interfacee, names;
    
        for interfacee in class_implements(eventName) {
            if isset this->listeners[interfacee] {
                for names in this->listeners[interfacee] {
                    let names = typeof names == "array" ? names : [names];
                    let listeners = array_merge(listeners, names);
                }
            }
        }
        return listeners;
    }
    
    /**
     * Determine if a given event has listeners.
     *
     * @param  string  $eventName
     * @return bool
     */
    public function hasListeners(string eventName) -> bool
    {
        return isset this->listeners[eventName];
    }
    
    /**
     * Remove a set of listeners from the dispatcher.
     *
     * @param  string  $event
     * @return void
     */
    public function remove(string event)
    {
        unset this->listeners[event];
    
    }

}