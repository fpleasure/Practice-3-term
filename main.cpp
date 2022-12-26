#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <ctime>
#include "header.h"
using namespace std;

int main(){
    setlocale(LC_ALL, "rus");
    string path = "/Users/nikitakorolev/Desktop/Прога/Практика/3 сем/Practice-3-term/Practice-3-term/test_graphs/examples_test5/problem.txt";
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
    
    clock_t start = clock();
    
    // Ввод решения в файл
    ofstream out("solution.txt");
    out << q << endl;
    
    // Маршруты
    for(int i = 0; i < q; i++){
        int a, b;
        file >> a;
        file >> b;
        vector<int> file(G.BellmanFord(a, b));
        //vector<int> file(G.findShortestRouteDFS(a, b));
        out << file.size() << endl;
        for (size_t i = 0; i < file.size(); ++i) {
            out << file.at(i) << " ";
        };
        out << endl;
        cout << endl;
    };
    out.close();
    cout << "Время выполнения в секундах = " << (clock()-start)/(CLOCKS_PER_SEC+0.0) << endl;
};
