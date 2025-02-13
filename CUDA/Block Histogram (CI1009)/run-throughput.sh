# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

echo "------------- BLOCO blockHisto_SM(): -----------"

echo "Executando 10 vezes com [nTotalElementos = 1048576 (2^20)] e [h=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
#1048576
#2097152
#4194304
#8388608
#16777216
    ./trab2 1048576 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 2097152 (2^21)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 2097152 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 4194304 (2^22)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 4194304 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 8388608 (2^23)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 8388608 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 16777216 (2^24)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 16777216 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "------------- BLOCO globalHisto_SM(): -----------"

echo "Executando 10 vezes com [nTotalElementos = 1048576 (2^20)] e [h=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
#1048576
#2097152
#4194304
#8388608
#16777216
    ./trab2 1048576 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 2097152 (2^21)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 2097152 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 4194304 (2^22)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 4194304 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 8388608 (2^23)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 8388608 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 16777216 (2^24)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 16777216 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "------------- BLOCO globalHisto_GM(): -----------"

echo "Executando 10 vezes com [nTotalElementos = 1048576 (2^20)] e [h=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
#1048576
#2097152
#4194304
#8388608
#16777216
    ./trab2 1048576 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 2097152 (2^21)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 2097152 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 4194304 (2^22)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 4194304 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 8388608 (2^23)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 8388608 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 16777216 (2^24)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 16777216 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done