#!/bin/bash

zep compile  > zim-compile.log 2>&1
OUT=$?
if [ $OUT -ne 0 ]; then
  echo "compile failed"
  exit 1;
fi
php bootstrap.php
