#!/bin/bash

docker build -t raygun4breakpad -f dockerfile ..

docker run -t -i --name raygun raygun4breakpad /bin/bash