#!/bin/bash

for i in {1..1}
do
	echo -e "\n\n### SENDING PAYLOAD ###\n";
	curl -v -H "x-apikey: $1" -F minidump=@build/mini.dmp $2/entries/breakpad;
	sleep 1;
done
echo -e "\n\n### FINISHED ###\n";