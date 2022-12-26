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
    bool dfs(int v1, int v2, vector<double>& distance, vector<int>& routes, vector<bool>& visited); // Алгоритм перебора
    vector<int> findShortestRouteDFS(int v1, int v2); // Вывод наименьшего пути перебора
    vector<int> BellmanFord(int v1, int v2); // Алгоритм Беллмана-Форда
    
};

/*-------------------------*/

Graph::Graph(int V){
    this->V = V;
    adj = new list< pair<int, double> >[V];
};

void Graph::addEdge(int v1, int v2, double cost){
    adj[v1].push_back({v2,cost});
};

bool Graph::dfs(int v1, int v2, vector<double>& distance, vector<int>& routes, vector<bool>& visited) {
    
    if(v1 == v2) return true;
    if(visited.at(v1)) return false;

    visited.at(v1) = true;
    
    for(auto & item : adj[v1]) {
        if(!visited.at(item.first)) {
            if((distance.at(item.first) > distance.at(v1)+item.second) or  (!distance.at(item.first))){
                
                distance.at(item.first) = distance.at(v1)+item.second;
                
                routes.at(item.first) = v1;
                
                
            }
            
            dfs(item.first, v2, distance, routes, visited);
            
            visited.at(item.first)=false;
            
        }
        
    }
    
    return false;
}

vector<int> Graph::findShortestRouteDFS(int v1, int v2){
    vector<bool> visited(this->V+1, false);
    vector<double> distance(this->V, 0);
    vector<int> routes (this->V, -1);
    dfs(v1, v2, distance, routes, visited);
    
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
    
    return path;
}

vector<int> Graph::BellmanFord(int v1, int v2){
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
                    
                    if(item.first == v2){ // Проверка на конечную вершину
                        continue;
                    }
                    
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
    
    return path;
};

#endif
