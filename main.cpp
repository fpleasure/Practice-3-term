/* Николай Назин и Никита Королев */
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "functions.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    string path = "/Users/nikitakorolev/Documents/Projects/Practice_3_sem/Practice_3_sem/problem.txt";
    ifstream file(path);
    
    int n; // Кол-во вершин
    file >> n;
    
    // Координаты точек
    vector < pair<double, double> > coordinates;
    for(int i = 0; i<n; i++){
        double x, y;
        file >> x;
        file >> y;
        coordinates.push_back({x,y});
    };
    
    int p; // Кол-во ребер
    file >> p;
    
    // Список смежности
    vector < pair<int, double> > unit[n+1];
    for(int i = 0; i<p; i++){
        int a, b;
        double s;
        file >> a;
        file >> b;
        file >> s;
        unit[a].push_back({b, s});
    };
    
    int q; // Кол-во ребер
    file >> q;
    
    // Маршруты
    vector < pair<int, int > > routes;
    for(int i = 0; i<q; i++){
        int a, b;
        file >> a;
        file >> b;
        routes.push_back({a, b});
    };
    
    queue<int> qu; // Очередь вершин
    bool visited[n+1]; // Список посещенных вершин
    double distance[n+1]; // Растояние от начальной вершины до всех остальных
    
    visited[1] = true;
    distance[1] = 0;
    qu.push(1);
    
    while (!qu.empty()){
        int adj = qu.front();
        qu.pop();
        
        for(auto& item : unit[adj])
        {
            
            /*
            cout<<"Из "<< adj;
            cout <<" в "<< item.first<<" ";
            cout<<"стоимость: " << item.second << endl;
            
            cout<<distance[item.first]<<endl;
             */
            
            distance[item.first] = distance[adj]+item.second;
            qu.push(item.first);
            //visited[item.first] = true;
        }
        
    }
    cout<<distance[2]<<endl;
    cout<<distance[3]<<endl;
    cout<<distance[4]<<endl;
}
