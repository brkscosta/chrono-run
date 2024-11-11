#!/bin/bash

cmake --build build || { echo "Failed to build project"; return 1; }