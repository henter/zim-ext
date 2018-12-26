# [WIP] The Zim Framework

### About

Zim is a simple framework inspired by Yaf, Laravel, Symfony, based on Zephir Language.

Delivered as a C extension for the PHP language, or you can choose the pure php implementation [zim-php](https://github.com/henter/zim-php)

The demo project [zim-demo](https://github.com/henter/zim-demo)

### Requirements

0. Zephir https://docs.zephir-lang.com/en/0.11/installation
1. PHP >= 7.0

### Install

```
git clone https://github.com/henter/zim-ext
cd zim-ext/ext
./install

php -m|grep zim
```

or build the extension manually, follow `ext/install` shell script

### Usage

simple demo with php build-in server

index.php
```php
<?php

use \Zim\Zim;
use \Zim\Routing\Route;

Route::get('/', function() {
    return 'hello zim';
});

Zim::run();

```

start simple server:

`php -S localhost:8888`

open [http://localhost:8888](http://localhost:8888)

more usage at [zim-demo](https://github.com/henter/zim-demo)

### Tests

see php version [zim-php](https://github.com/henter/zim-php)

### Documentation

TODO

### Contributing

Welcome !

### Licence

MIT
