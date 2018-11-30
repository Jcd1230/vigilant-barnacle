#!/usr/bin/env sh
# This must be run as root

perf stat -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores ./aos-example
perf stat -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores ./soa-example
