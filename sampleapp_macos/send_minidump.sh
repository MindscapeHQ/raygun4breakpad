#!/bin/bash

curl -v -H "x-apikey: $1" -F minidump=@build/mini.dmp $2/entries/breakpad
