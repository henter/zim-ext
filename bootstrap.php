<?php
/**
 * File bootstrap.php
 * @henter
 * Time: 2018-11-24 19:12
 *
 */

//require_once __DIR__.'/../vendor/autoload.php';

define('APP_PATH', '/Users/henter/Dev/zim-php/app');

function getRequest($method, $uri)
{
    $query = $request = $attr = $server = [];
    $server['REQUEST_METHOD'] = $method;
    $server['REQUEST_URI'] = $uri;
    return new \Zim\Http\Request($query, $request, $attr, $server);
}


//$zim = Zim\Zim::getInstance();
$zim = new \Zim\Zim();

////try call
//$callable = function($page = 1) {
//    return 'page '.$page;
//};
//$ret = $zim->call($callable, ['page' => 333]);
//var_dump($ret);
//return;


$zim->singleton(\Zim\Http\Kernel::class);

$http = $zim->make(\Zim\Http\Kernel::class);


\Zim\Routing\Route::post('/test_route1/{page<\d+>?123}', function($page = 2) {
    return 'test ok';
});


$request = getRequest('GET', '/test_route1/333');
$response = $http->handle($request);
var_dump($response);

//return $zim;

