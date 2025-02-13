# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

#echo "------------- BLOCO reduceMax_coalesced(): -----------"

#echo "------------- BLOCO 1000000: -----------"

#echo "------------- avg_time_coalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 1000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 1000000 30 | grep -oP '(?<=(avg_time_coalesced): )[^ ]*'
done

#echo "------------- throughput_coalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 1000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 1000000 30 | grep -oP '(?<=(throughput_coalesced): )[^ ]*'
done

#echo "------------- BLOCO 16000000: -----------"

#echo "------------- avg_time_coalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 16000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 16000000 30 | grep -oP '(?<=(avg_time_coalesced): )[^ ]*'
done

#echo "------------- throughput_coalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 16000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 16000000 30 | grep -oP '(?<=(throughput_coalesced): )[^ ]*'
done

#echo "------------- BLOCO reduceMax_blockCoalesced(): -----------"

#echo "------------- BLOCO 1000000: -----------"

#echo "------------- avg_time_blockCoalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 1000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 1000000 30 | grep -oP '(?<=(avg_time_blockCoalesced): )[^ ]*'
done

#echo "------------- throughput_blockCoalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 1000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 1000000 30 | grep -oP '(?<=(throughput_blockCoalesced): )[^ ]*'
done

#echo "------------- BLOCO 16000000: -----------"

#echo "------------- avg_time_blockCoalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 16000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 16000000 30 | grep -oP '(?<=(avg_time_blockCoalesced): )[^ ]*'
done

#echo "------------- throughput_blockCoalesced: -----------"
echo "Executando 10 vezes com [nTotalElementos = 16000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 16000000 30 | grep -oP '(?<=(throughput_blockCoalesced): )[^ ]*'
done

#echo "------------- speedup: -----------"
echo "Executando 10 vezes com [nTotalElementos = 1000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 1000000 30 | grep -oP '(?<=(speedup): )[^ ]*'
done

echo "Executando 10 vezes com [nTotalElementos = 16000000] e [nR=30]:"
for vez in {1..10}  # 10 vezes
do
    ./trab3 16000000 30 | grep -oP '(?<=(speedup): )[^ ]*'
done