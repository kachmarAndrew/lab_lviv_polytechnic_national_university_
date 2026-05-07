#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    unordered_map<string, vector<string>> graph;

    graph["Львів"] = {"Ковель", "Івано-Франківськ"};
    graph["Ковель"] = {"Львів", "Рівне"};
    graph["Рівне"] = {"Ковель", "Київ"};
    graph["Київ"] = {"Рівне", "Вінниця"};
    graph["Вінниця"] = {"Київ", "Івано-Франківськ"};
    graph["Івано-Франківськ"] = {"Вінниця", "Львів"};

    for (const auto& city : graph) {
        cout << city.first << " -> ";

        for (const auto& neighbor : city.second) {
            cout << neighbor << " ";
        }

        cout << endl;
    }

    return 0;
}