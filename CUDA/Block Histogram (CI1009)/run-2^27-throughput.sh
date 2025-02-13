# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

echo "------------- BLOCO blockHisto_SM(): -----------"

echo "Executando 10 vezes com [nTotalElementos = 134.217.728 (2^27)] e [h=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    ./trab2 134217728 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done
echo "Executando 10 vezes com [nTotalElementos = 268.435.456 (2^28)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 268435456 2048 -bh | grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "------------- BLOCO globalHisto_SM(): -----------"

echo "Executando 10 vezes com [nTotalElementos = 134.217.728 (2^27)] e [h=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    ./trab2 134217728 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done
echo "Executando 10 vezes com [nTotalElementos = 268.435.456 (2^28)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 268435456 2048 -gh| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done

echo "------------- BLOCO globalHisto_GM(): -----------"

echo "Executando 10 vezes com [nTotalElementos = 134.217.728 (2^27)] e [h=2048]:"
#for vez in {1..1}   # 1 vez
for vez in {1..10}  # 10 vezes
do
    ./trab2 134217728 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done
echo "Executando 10 vezes com [nTotalElementos = 268.435.456 (2^28)] e [h=2048]:"
for vez in {1..10}  # 10 vezes
do
    ./trab2 268435456 2048 -ghgm| grep -oP '(?<=(Throughput_ em GOP/ms): )[^ ]*'
done