#!/bin/bash
echo "USAGE: ./run.sh <nq> <np> <D> <k>"
    

echo "Executando 10 vezes com 1 thread  (local),   [$1] pontos em Q, [$2] pontos em P, [$3] dimensões, e k = [$4]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    mpirun -n 1 ./trab5 $1 $2 $3 $4 | grep -oP '(?<=total_time_in_seconds: )[^ ]*'
done

echo "Executando 10 vezes com 4 threads (local),   [$1] pontos em Q, [$2] pontos em P, [$3] dimensões, e k = [$4]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    mpirun -n 4 ./trab5 $1 $2 $3 $4 | grep -oP '(?<=total_time_in_seconds: )[^ ]*'
done

echo "Executando 10 vezes com 4 threads (cluster), [$1] pontos em Q, [$2] pontos em P, [$3] dimensões, e k = [$4]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    mpirun -n 4 --hostfile hostfile.txt ./trab5 $1 $2 $3 $4 | grep -oP '(?<=total_time_in_seconds: )[^ ]*'
done