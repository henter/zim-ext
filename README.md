# The Zim Framework

### About

Zim is a simple framework inspired(copy/paste 😄) by Yaf, Laravel, Symfony, based on Zephir Language.

Delivered as a C extension for the PHP language via [zim-ext](https://github.com/henter/zim-ext) , or you can choose the pure php implementation [zim-php](https://github.com/henter/zim-php)

The demo project [zim](https://github.com/henter/zim)

### Requirements

0. Zephir https://docs.zephir-lang.com/en/0.11/installation
1. PHP >= 7.0

### Install

* requires `phpize`, `php-config` (from `php-devel` extension)
```
git clone https://github.com/henter/zim-ext
cd zim/ext
```
run `install` to compile && install zim.so file
```
./install
```

or build the extension manually, follow `ext/install` shell script

```
/path/to/phpize
./configure --with-php-config=/path/to/php-config
make && make install
```

Then enable zim extension to your php.ini (after json.so)

```
extension=zim.so
```

check if is installed successful
```
php -m|grep zim
```

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

more usage at [zim](https://github.com/henter/zim)

### Tests

see php version [zim-php](https://github.com/henter/zim-php)

### Documentation

TODO

### Contributing

Welcome !

### Licence

MIT
