#!/usr/bin/env sh
# This must be run as root

#perf_opts="perf stat -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores"
perf_opts="/usr/bin/time"

echo 'Malloc:'
time ./malloc-example

echo 'AoS:'
time ./aos-example

echo 'SoA:'
time ./soa-example