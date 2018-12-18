<?php
/**
 * File bootstrap.php
 * @henter
 * Time: 2018-11-24 19:12
 *
 */

////require_once __DIR__.'/../vendor/autoload.php';
//
//define('APP_PATH', '/Users/henter/Dev/zim-php/app');
//
//function getRequest($method, $uri)
//{
//    $query = $request = $attr = $server = [];
//    $server['REQUEST_METHOD'] = $method;
//    $server['REQUEST_URI'] = $uri;
//    return new \Zim\Http\Request($query, $request, $attr, $server);
//}
//
////$zim = Zim\Zim::getInstance();
//$zim = new \Zim\Zim();
//$zim->singleton(\Zim\Http\Kernel::class);
//
//$http = $zim->make(\Zim\Http\Kernel::class);
//
//$request = getRequest('GET', 'test_route1/333');
//$response = $http->handle($request);
//var_dump($response);

//return $zim;

$route = new \Zim\Routing\Route('/test/{page<\d+>?123}');
var_dump($route->compile()->getRegex());
