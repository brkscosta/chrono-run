#!/bin/bash

cmake --build build --config Debug || { echo "Failed to build project"; return 1; }