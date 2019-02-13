#!/bin/bash

set -e

TAG="$1"

echo --------------------------
echo ${TAG}MultikeyMap_test
./${TAG}MultikeyMap_test
echo --------------------------
echo ${TAG}MultikeyMap_test2
./${TAG}MultikeyMap_test2
