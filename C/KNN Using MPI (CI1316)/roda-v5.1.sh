#!/bin/bash
echo "USAGE: ./run.sh <nq> <np> <D> <k>"
    

echo "(bônus) Executando 10 vezes com 16 threads (cluster), [$1] pontos em Q, [$2] pontos em P, [$3] dimensões, e k = [$4]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    mpirun -n 16 --hostfile hostfile.txt ./trab5 $1 $2 $3 $4 | grep -oP '(?<=total_time_in_seconds: )[^ ]*'
done