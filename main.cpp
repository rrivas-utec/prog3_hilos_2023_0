#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

void f1() {
    cout << "Mi primer hilo\n";
}


void ejemplo_hilos_simples() {
    thread t1;                // Hilo Vacio
    vector<thread> vh(2);     // Coleccion de Hilos Vacios

    thread t2(f1);       // Hilo con funcion determinada
    thread t3(f1);
    //... mas codigo
    cout << "Esperado fin de hilo 2\n";
    t2.join();              // Obligatorio

    //... mas codigo
    t3.detach();            // No esperes el hilo
    //... mas codigo
}


void f2(int a, int b, int& total) {
    total = a + b;
}

void ejemplo_hilo_parametros() {
    int total = 0;
    thread t1(f2, 10, 20, ref(total));
    t1.join();
    // El resultado de un hilo debe evaluarse luego del join
    cout << total;
}

// Se necesita adicionalmente a los hilos el uso de lambdas
int f3(int a, int b) {
    return a + b;
}

void ejemplo_hilo_parametros_lambda() {
    int total = 0;
    auto lambda = [&total] { total = f3(10, 20); };
    thread t1(lambda);
    t1.join();
    cout << total;
}

class A {
public:
    void m1(int a, int b, int& total) {
        total = a + b;
    }

    int m2(int a, int b) {
        return a + b;
    }
};

void ejemplo_hilo_asignado_metodo() {
    A obj_a;
    int total = 0;
    /**
    PARA UNA FUNCION: los parametros del hilo
        1. Nombre de funcion
        2. Lista de parametros de funcion

    PARA METODOS : los parametros del hilo
        1. La direccion del metodo
        2. La direccion del objeto
        3. La lista de parametros del metodo
     **/
    thread t1(&A::m1, &obj_a, 4, 20, ref(total));
    t1.join();
    cout << total;
}

void ejemplo_hilo_asignado_metodo_lambda() {
    A obj_a;
    int total = 0;
    thread t1([&obj_a, &total] { obj_a.m1(10, 40, total); });
    t1.join();
    cout << total;
}

void ejemplo_hilo_vacio() {
    thread t1;          // Hilo vacio
    //...
    t1 = thread(f1);    // Asignamos funcion - Comienza ejecutar
    t1.join();
}

void sumar_rango(int start, int stop, vector<int>& data, int& total) {
    total = 0;
    for (int i = start; i < stop; ++i)
        total += data[i];
}

ostream& operator<<(ostream& os, const vector<int>& v) {
    for (const auto& item: v)
        os << item << " ";
    return os;
}

void ejemplo_vector_hilos() {
    random_device rd;

    // vector aleatorio de 100 valores
    vector<int> v1 (100);
    for (auto& item: v1)
        item = rd() % 20;

//    cout << v1 << endl;

    int total = 0;
    for (const auto& item: v1)
        total += item;
    cout << total << endl;
//
    vector<int> resultados(4);
    thread t1(sumar_rango, 0, 25, ref(v1), ref(resultados[0]));
    thread t2(sumar_rango, 25, 50, ref(v1), ref(resultados[1]));
    thread t3(sumar_rango, 50, 75, ref(v1), ref(resultados[2]));
    thread t4(sumar_rango, 75, 100, ref(v1), ref(resultados[3]));
//
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();

//    auto total_final = accumulate(begin(rt), end(rt), 0);
//    cout << total_final << endl;
}

int main() {
//    ejemplo_hilos_simples();
//    ejemplo_hilo_parametros();
//    ejemplo_hilo_asignado_metodo();
//    ejemplo_hilo_asignado_metodo_lambda();
//    ejemplo_hilo_vacio();
    ejemplo_vector_hilos();
    return 0;
}
