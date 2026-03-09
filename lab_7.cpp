#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class RecipeSystem {
private:
    unordered_map<string, string> recipes;

public:
    void addRecipe(string name, string description) {
        recipes[name] = description;
        cout << "Recipe added successfully!\n";
    }

    void findRecipe(string name) {
        if (recipes.find(name) != recipes.end()) {
            cout << "Recipe found:\n";
            cout << name << " -> " << recipes[name] << endl;
        } else {
            cout << "Recipe not found.\n";
        }
    }

    void deleteRecipe(string name) {
        if (recipes.erase(name)) {
            cout << "Recipe deleted.\n";
        } else {
            cout << "Recipe not found.\n";
        }
    }

    void showAllRecipes() {
        if (recipes.empty()) {
            cout << "No recipes available.\n";
            return;
        }

        cout << "\nAll recipes:\n";
        for (auto &recipe : recipes) {
            cout << recipe.first << " -> " << recipe.second << endl;
        }
    }
};

int main() {
    RecipeSystem system;
    int choice;
    string name, description;

    do {
        cout << "\n=== Recipe System ===\n";
        cout << "1. Add recipe\n";
        cout << "2. Find recipe\n";
        cout << "3. Delete recipe\n";
        cout << "4. Show all recipes\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter recipe name: ";
            getline(cin, name);
            cout << "Enter recipe description: ";
            getline(cin, description);
            system.addRecipe(name, description);
            break;

        case 2:
            cout << "Enter recipe name: ";
            getline(cin, name);
            system.findRecipe(name);
            break;

        case 3:
            cout << "Enter recipe name: ";
            getline(cin, name);
            system.deleteRecipe(name);
            break;

        case 4:
            system.showAllRecipes();
            break;
        }

    } while (choice != 0);

    return 0;
}