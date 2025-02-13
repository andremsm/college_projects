# FEITO POR:
# André Miguel Sikora Marques
# GRR20182593

echo Compilando blockHisto.cu...
echo nvcc -arch sm_61 --std=c++14 -o trab2 blockHisto.cu
nvcc -arch sm_61 --std=c++14 -o trab2 blockHisto.cu