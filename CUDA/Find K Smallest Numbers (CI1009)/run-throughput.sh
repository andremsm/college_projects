# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

echo "------------- BLOCO PARALELO: -----------"

echo "Executando 10 vezes com [nTotalElementos = 1048576 (2^20)] e [heapSize=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
#1048576
#2097152
#4194304
#8388608
#16777216
    ./trab1 1048576 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 2097152 (2^21)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab1 2097152 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 4194304 (2^22)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab1 4194304 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 8388608 (2^23)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab1 8388608 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 16777216 (2^24)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab1 16777216 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "------------- BLOCO SEQUENCIAL: -----------"

echo "Executando 10 vezes com [nTotalElementos = 1048576 (2^20)] e [heapSize=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
#1048576
#2097152
#4194304
#8388608
#16777216
    ./seq 1048576 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 2097152 (2^21)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./seq 2097152 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 4194304 (2^22)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./seq 4194304 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 8388608 (2^23)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./seq 8388608 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 16777216 (2^24)] e [heapSize=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./seq 16777216 2048 | grep -oP '(?<=(Throughput em MOPS): )[^ ]*'
done