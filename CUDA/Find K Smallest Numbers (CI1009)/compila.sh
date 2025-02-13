# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

echo Compilando programa paralelo...
echo nvcc -arch sm_61 --std=c++14 -o trab1 acharKmenores.cu
nvcc -arch sm_61 --std=c++14 -o trab1 acharKmenores.cu

echo Compilando programa sequencial...
echo g++ seq.c -o seq -lm
g++ seq.c -o seq -lm
