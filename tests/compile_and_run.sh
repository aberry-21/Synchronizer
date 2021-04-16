#!/bin/bash

mkdir -p build && cd build && cmake .. && make && ./synchronizer_tests
