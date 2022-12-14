#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include "header.h"
using namespace std;

int main(){
    
    setlocale(LC_ALL, "rus");
    string path = "/Users/nikitakorolev/Desktop/Прога/Практика/3 сем/Practice-3-term/Practice-3-term/examples_test3/problem.txt";
    ifstream file(path);
    
    int n; // Кол-во вершин
    file >> n;
    
     
    // Координаты точек
    vector < pair<double, double> > coordinates;
    for(int i = 0; i < n; i++){
        double x, y;
        file >> x;
        file >> y;
        coordinates.push_back({x,y});
    };
    
     
    
    int p; // Кол-во ребер
    file >> p;
    
    // Создаем граф
    Graph G(n+1);

    // Список смежности
    for(int i = 0; i < p; i++){
        int a, b;
        double s;
        file >> a;
        file >> b;
        file >> s;
        G.addEdge(a, b, s);
    };
    
    int q; // Кол-во ребер
    file >> q;
    
    // Маршруты
    for(int i = 0; i < q; i++){
        int a, b;
        file >> a;
        file >> b;
        cout<<"БЕЛЛМАН-ФОРД"<<endl;
        G.BellmanFord(a, b);
        cout<<"ПЕРЕБОР"<<endl;
        G.findShortestRouteEnum(a, b);
        cout<<endl;
    };
    
    
};
