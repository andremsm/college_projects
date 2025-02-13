# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

echo Compilando reduceMax.cu...
echo nvcc -arch sm_61 --std=c++14 -o trab3 reduceMax.cu
nvcc -arch sm_61 --std=c++14 -o trab3 reduceMax.cu