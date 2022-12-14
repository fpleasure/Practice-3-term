#ifndef vortex_methods
#define vortex_methods
#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Graph{
    int V; // Количество вершин
    list< pair <int, double> > *adj;
public:
    Graph(int V); // Конструктор
    void addEdge(int v1, int v2, double cost); // Добавить ребро
    void findShortestRouteEnum(int v1, int v2);// Поиск кратчайшего пути от вершины v1  до v2
    void BellmanFord(int v1, int v2); // Алгоритм Беллмана-Форда
};

/*-------------------------*/

Graph::Graph(int V){
    this->V = V;
    adj = new list< pair<int, double> >[V];
};

void Graph::addEdge(int v1, int v2, double cost){
    adj[v1].push_back({v2,cost});
};

void Graph::findShortestRouteEnum(int v1, int v2){
    queue<int> qu; // Очередь вершин
    vector<bool> visited(this->V+1, false); // Список посещенных вершин
    vector<double> distance(this->V+1, 0); // Растояние от начальной вершины до всех остальных
    vector<int> routes (this->V, -1);
    
    // Добавляем вершину в очередь
    qu.push(v1);
    
    while(!qu.empty()){
        int ad = qu.front();
        qu.pop();
        
        for(auto & item : adj[ad]){
            
            if((distance.at(item.first) > distance.at(ad)+item.second) or (!distance.at(item.first))){
                
                distance.at(item.first) = distance.at(ad)+item.second;
                // Сохраняем путь
                routes.at(item.first) = ad;
                
                qu.push(item.first);
                
                visited.at(item.first) = true;
                //cout<<ad<<endl;
            }
            
            if(item.first == v2){ // Проверка на конечную вершину
                continue;
            }
        }
    };
    
    vector<int> path;
        
    // Проходимся по "предкам" пути
    for(int i = v2; i != -1; i = routes.at(i)){
        path.push_back(i);
        if(i==v1) break;
    }
    
    // Так как проходили "снизу" "наверх"
    // переворачиваем массив
    reverse (path.begin(), path.end());
        
    cout << "Путь от вершины " << v1 << " до вершины " << v2 << ": ";
        
    for (size_t i=0; i<path.size(); ++i){
        cout << path.at(i) << " ";
    };
        
    cout<<endl<<endl<<"Кол-во узлов: "<<path.size()<<endl;
    
    
    cout << endl << "Расстояние: " << distance.at(v2) << endl;
};

void Graph::BellmanFord(int v1, int v2){
    const int INF = 1000000000;
    vector<double> distance(this->V, INF);
    vector<int> routes(this->V, -1);
    
    distance.at(v1) = 0;
    
    while(true){
        bool any = false;
        for(int j = 0; j < this->V; j++){
            for(const auto & item : adj[j]){
                
                if((distance.at(j)<INF) and ( distance.at(item.first) > distance.at(j)+item.second )){
                    
                    distance.at(item.first) = distance.at(j)+item.second;
                    // Сохраняем путь
                    routes.at(item.first) = j;
                    
                    any = true;
                    
                    
                }
            }
        }
        if (!any)  break;
       
    }
    
  
    vector<int> path;
        
    // Проходимся по "предкам" пути
    for(int i = v2; i != -1; i = routes.at(i)){
        path.push_back(i);
        if(i==v1) break;
    }
    
    // Так как проходили "снизу" "наверх"
    // переворачиваем массив
    reverse (path.begin(), path.end());
        
    cout << "Путь от вершины " << v1 << " до вершины " << v2 << ": ";
        
    for (size_t i=0; i<path.size(); ++i){
        cout << path.at(i) << " ";
    };
        
    cout<<endl<<endl<<"Кол-во узлов: "<<path.size()<<endl;
    
    
    cout << endl << "Расстояние: " << distance.at(v2) << endl;
};

#endif
