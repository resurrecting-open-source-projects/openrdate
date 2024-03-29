#!/bin/bash

# Copyright 2015-2019 Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
# Create a manpage using txt2man command.
#
# This script can be used under BSD-3-Clause license.

T2M_DATE="14 Feb 2022"
T2M_NAME=rdate
T2M_VERSION=1.11
T2M_LEVEL=8
T2M_DESC="set the system's date from a remote host"

# Don't change the following lines
TEST=$(txt2man -h 2> /dev/null)
[ "$TEST" ] || { echo -e "\nYou need to install txt2man, from https://github.com/mvertes/txt2man.\n"; exit 1; }

txt2man -d "$T2M_DATE" -t $T2M_NAME -r $T2M_NAME-$T2M_VERSION -s $T2M_LEVEL -v "$T2M_DESC" $T2M_NAME.txt > $T2M_NAME.$T2M_LEVEL
