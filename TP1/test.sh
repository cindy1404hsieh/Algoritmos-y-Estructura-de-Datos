#!/bin/bash

make -f makefile-chanutron clean 2>&1
make -f makefile-chanutron valgrind 2>&1

