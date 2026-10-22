#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
cc -O3 -std=c11 -fno-fast-math -ffp-contract=off -c runtime_stub.c -o runtime_stub.o
cc -O3 -std=c11 -fno-fast-math -ffp-contract=off -c variants.c -o variants.o
cc -O3 -std=c11 -fno-fast-math -ffp-contract=off -c diagnostic.c -o diagnostic.o
cc runtime_stub.o variants.o diagnostic.o -lm -o diagnostic
./diagnostic "$@"
