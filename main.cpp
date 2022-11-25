/* Николай Назин и Никита Королев */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Graph{
    int V; // Количество вершин
    list<pair<int, double>> *adj;
public:
    Graph(int V); // Конструктор
    void addEdge(int v1, int v2, double cost); // Добавить ребро
    void findShortestRouteEnum(int v1, int v2);// Поиск кратчайшего пути от вершины v1  до v2
    void BellmanFord(int v1, int v2); // Алгоритм Беллмана-Форда
};

Graph::Graph(int V){
    this->V = V;
    adj = new list<pair<int, double>>[V];
};

void Graph::addEdge(int v1, int v2, double cost){
    adj[v1].push_back({v2,cost});
};

void Graph::findShortestRouteEnum(int v1, int v2){
    queue<int> qu; // Очередь вершин
    vector<bool> visited(this->V+1, false); // Список посещенных вершин
    vector<double> distance(this->V+1, 0); // Растояние от начальной вершины до всех остальных
    vector<double> routes (this->V, -1);
    
    qu.push(v1); // Добавляем вершину в очередь
    while (!qu.empty()){
        int ad = qu.front();
        qu.pop();
                
        for(auto & item : adj[ad]){
                    
            if(visited.at(item.first)){
                continue;
                // Проверка на посещенные вершины
            }
            
            if ((distance.at(item.first) > distance.at(ad)+item.second) or (!distance.at(item.first))){
                distance.at(item.first) = distance.at(ad)+item.second;
                // Сохраняем путь
                routes.at(item.first) = ad;
            }
            
            
            
            if(item.first == v2){
                continue;
                // Проверка на конечную вершину
            }
            
            qu.push(item.first);
            visited.at(item.first) = true;
            
        }
                
    };
    
    if(distance.at(v2) == 0){
        cout << "Нет пути от вершины " << v1 << " до вершины " << v2 << endl;
    }
    else{ // Вывод пути
        vector<int> path;
        
        // Проходимся по "предкам" пути
        for(int i = v2; i != -1; i = routes.at(i)){
            path.push_back(i);
        }
        // Так как проходили с "низу" на "верх"
        // переворачиваем массив
        reverse (path.begin(), path.end());
        cout<<"Путь от вершины "<< v1 << " до вершины " << v2 << ": ";
        
        for (size_t i=0; i<path.size(); ++i){
            cout << path.at(i) << " ";
        }
    }

    
    cout<<endl;
    cout<<"Расстояние: " << distance.at(v2) << endl;
};

void Graph::BellmanFord(int v1, int v2){
    const int INF = 1000000000;
    vector<int> distance(this->V, INF);
    vector<double> routes (this->V, -1);
    
    distance.at(v1) = 0;
    
    // Пробегаем V-1 раз по каждому ребру
    for (int i = 0; i<this->V-1; ++i){
        for(int j = 0; j<this->V-1; ++j){
            for(auto & item : adj[j]){
                
                if((distance.at(j)<INF) and (distance.at(item.first)>distance.at(j)+item.second)){
                    distance.at(item.first) = distance.at(j)+item.second;
                    // Сохраняем путь
                    routes.at(item.first) = j;
                    
                }
            }
        }
    }
    
    if(distance.at(v2) == INF){
        cout << "Нет пути от вершины " << v1 << " до вершины " << v2 << endl;
    }
    else{ // Вывод пути
        vector<int> path;
        
        // Проходимся по "предкам" пути
        for(int i = v2; i != -1; i = routes.at(i)){
            path.push_back(i);
        }
        // Так как проходили "снизу" "наверх"
        // переворачиваем массив
        reverse (path.begin(), path.end());
        
        cout<<"Путь от вершины "<< v1 << " до вершины " << v2 << ": ";
        
        for (size_t i=0; i<path.size(); ++i){
            cout << path.at(i) << " ";
        }
    }
    cout<<endl;
    cout<<"Расстояние: " << distance.at(v2) << endl;
};

int main(){
    
    setlocale(LC_ALL, "rus");
    string path = "/Users/nikitakorolev/Desktop/Прога/Практика/3 сем/Practice-3-term/Practice-3-term/examples/problem.txt";
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
    
    // Создаем граф
    Graph G(n+1);

    // Список смежности
    for(int i = 0; i<p; i++){
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
    for(int i = 0; i<q; i++){
        int a, b;
        file >> a;
        file >> b;
        G.BellmanFord(a, b);
        cout<<endl;
        //G.findShortestRouteEnum(a, b);
    };
};
