#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // Вершини
    vector<string> cities = {"Київ", "Біла Церква", "Бровари", "Васильків", "Фастів"};
    int n = cities.size();

    // Ребра і відстані (км)
    // Кожне ребро: {з вершини, до вершини, вага (км)}
    vector<tuple<int,int,double>> edges = {
        {0, 1, 40}, // Київ - Біла Церква
        {0, 2, 30}, // Київ - Бровари
        {0, 3, 20}, // Київ - Васильків
        {0, 4, 50}, // Київ - Фастів
        {1, 4, 60}  // Біла Церква - Фастів
    };
    int m = edges.size();

    // Матриця суміжності
    vector<vector<double>> adjMatrix(n, vector<double>(n, 0));
    for(auto& e : edges) {
        int u = get<0>(e);
        int v = get<1>(e);
        double w = get<2>(e);
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // неорієнтований граф
    }

    // Вивід матриці суміжності
    cout << "Adjacency matrix:\n";
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << adjMatrix[i][j] << "\t";
        }
        cout << "\n";
    }

    // Матриця інцидентності
    vector<vector<int>> incMatrix(n, vector<int>(m, 0));
    for(int j = 0; j < m; ++j){
        int u = get<0>(edges[j]);
        int v = get<1>(edges[j]);
        incMatrix[u][j] = 1;
        incMatrix[v][j] = 1;
    }

    // Вивід матриці інцидентності
    cout << "\nIncidence matrix:\n";
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << incMatrix[i][j] << "\t";
        }
        cout << "\n";
    }

    return 0;
}