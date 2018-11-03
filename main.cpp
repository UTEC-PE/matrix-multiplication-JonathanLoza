#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

#define NUM_THREADS 2

int numerothreads(int &filasporthread, int &restante,int  n);
void rellenar(int** matriz1,int**matriz2 ,int** respuesta, int fila, int cantidad, int c);
void rellenarMatriz(int filas, int columnas, int** matriz) ;

int main(){

  int rows=2;
  int cols=2;
  int** matriz1 = new int*[rows];
  for (int i = 0; i < rows; ++i)
        matriz1[i] = new int[cols];

  int** matriz2 = new int*[rows];
  for (int i = 0; i < rows; ++i)
      matriz2[i] = new int[cols];
  rellenarMatriz(rows, cols, matriz1);
  rellenarMatriz(rows, cols, matriz2);

  int **resultado = new int*[2];
  for(int i=0;i<2;i++){
      resultado[i] = new int[2];
  }
  int nrows=0;
  int diferencia=0;
  int nthreads=numerothreads(nrows,diferencia,2);
  //cout<<nthreads<<endl;
  //cout<<nrows<<endl;
  //cout<<diferencia<<endl;
  thread threads[nthreads];
  int primerafila=0;
  for (int i = 0; i < nthreads; ++i) {
    if(diferencia!=0){
      threads[i] = thread(rellenar, matriz1,matriz2, resultado, primerafila,nrows+1,cols);
      primerafila=+nrows+1;
      diferencia--;
    }else{
      threads[i] = thread(rellenar, matriz1,matriz2, resultado, primerafila,nrows,cols );
      primerafila=+nrows;
    }
  }

  for (int i = 0; i < nthreads; ++i) {
      threads[i].join();
  }

  for(int i=0;i<2;i++){
    for(int j=0; j<2; j++){
      cout<<resultado[i][j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}

int numerothreads(int &filasporthread, int &restante,int  n){
  if(NUM_THREADS>= n){
    filasporthread=1;
    restante=0;

    return n;
  }else{
    restante=n%NUM_THREADS;
    filasporthread=(n-restante)/NUM_THREADS;

    return NUM_THREADS;
  }
};

void rellenar(int** matriz1,int**matriz2 ,int** respuesta, int fila, int cantidad, int c){
  for (int i = fila; i <= cantidad; ++i) {
    for (int j = 0; j < c; ++j) {
      int result = 0;
      for (int k = 0; k < c; ++k) {
        int e1 = matriz1[i][k];
        int e2 = matriz2[k][j];
        result += e1 * e2;
      }
      respuesta[i][j] = result;
    }
  }
};
void rellenarMatriz(int filas, int columnas, int** matriz) {
    cout<<"\nDigitando datos para la matriz: \n";
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            cout<<"Ingrese["<<i<<"]["<<j<<"]: ";
            cin>>matriz[i][j];
        }
    }
}
