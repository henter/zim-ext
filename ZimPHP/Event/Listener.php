<?php
/**
 * File Event.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */

namespace Zim\Event;

class Listener
{
    private $callback;

    public function __construct($callback)
    {
        $this->callback = $callback;
    }

    public function __invoke($event, $payload)
    {
        $callback = $this->callback;
        return $callback($event, $payload);
    }

}