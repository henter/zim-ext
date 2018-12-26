/**
 * File Event.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */
namespace Zim\Event;

class ListenerOn
{
    protected callback;
    public function __construct(callback) -> void
    {
        let this->callback = callback;
    }
    
    public function __invoke(event, payload)
    {
        var callback;

        let callback = this->callback;
        return {callback}(payload);
    }

}