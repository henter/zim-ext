<?php
/**
 * File bootstrap.php
 * @henter
 * Time: 2018-11-24 19:12
 *
 */

//require_once __DIR__.'/../vendor/autoload.php';

define('APP_PATH', '/Users/henter/Dev/zim-php/app');

//Route::match(['GET', 'POST'], '/henter', function(\Zim\Http\Request $req, \Zim\Config\Config $config) {
//    return new \Zim\Http\JsonResponse([
//        'req_path' => $req->getPathInfo(),
//        'config' => $config->all(),
//    ]);
//});

//$zim = Zim\Zim::getInstance();
$zim = new \Zim\Zim();
$zim->singleton(\Zim\Http\Kernel::class);

return $zim;
