#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Структура Player
struct Player {
    string name;
    string position;
    int goals;
    int matches;
    double rating;
};

// Функція для додавання нового гравця
void addPlayer(vector<Player>& team, const string& name, const string& position, int goals, int matches, double rating) {
    team.push_back({name, position, goals, matches, rating});
    cout << "Гравця \"" << name << "\" додано до команди." << endl;
}

// Функція для виведення інформації про всіх гравців
void displayPlayers(const vector<Player>& team) {
    if (team.empty()) {
        cout << "Команда порожня." << endl;
        return;
    }

    cout << left << setw(15) << "Ім'я" 
         << setw(15) << "Позиція" 
         << setw(10) << "Голи" 
         << setw(10) << "Матчі" 
         << setw(10) << "Рейтинг" << endl;
    cout << string(60, '-') << endl;

    for (const auto& player : team) {
        cout << left << setw(15) << player.name 
             << setw(15) << player.position 
             << setw(10) << player.goals 
             << setw(10) << player.matches 
             << setw(10) << fixed << setprecision(2) << player.rating << endl;
    }
}

// Функція для пошуку гравців за позицією
void searchPlayersByPosition(const vector<Player>& team, const string& position) {
    cout << "\nГравці на позиції \"" << position << "\":" << endl;

    bool found = false;
    for (const auto& player : team) {
        if (player.position == position) {
            cout << player.name << " (" << player.goals << " голів, " 
                 << player.rating << " рейтинг)" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Гравців на цій позиції не знайдено." << endl;
    }
}

// Функція для підрахунку загальної кількості голів команди
int totalGoals(const vector<Player>& team) {
    int total = 0;
    for (const auto& player : team) {
        total += player.goals;
    }
    return total;
}

// Функція для визначення найкращого бомбардира
void findTopScorer(const vector<Player>& team) {
    if (team.empty()) {
        cout << "Команда порожня." << endl;
        return;
    }

    const Player* topScorer = &team[0];
    for (const auto& player : team) {
        if (player.goals > topScorer->goals) {
            topScorer = &player;
        }
    }

    cout << "Найкращий бомбардир: " << topScorer->name 
         << " (" << topScorer->goals << " голів)" << endl;
}

// Функція для визначення гравця з найвищим рейтингом
void findTopRatedPlayer(const vector<Player>& team) {
    if (team.empty()) {
        cout << "Команда порожня." << endl;
        return;
    }

    const Player* topRated = &team[0];
    for (const auto& player : team) {
        if (player.rating > topRated->rating) {
            topRated = &player;
        }
    }

    cout << "Гравець з найвищим рейтингом: " << topRated->name 
         << " (" << topRated->rating << ")" << endl;
}

// Функція для формування складу команди на основі рейтингу
void selectBestTeam(const vector<Player>& team, int maxPlayers) {
    if (team.empty()) {
        cout << "Команда порожня." << endl;
        return;
    }

    vector<Player> sortedTeam = team;
    sort(sortedTeam.begin(), sortedTeam.end(), [](const Player& a, const Player& b) {
        return a.rating > b.rating;
    });

    cout << "\nОптимальний склад команди (" << maxPlayers << " гравців):" << endl;
    for (int i = 0; i < maxPlayers && i < sortedTeam.size(); ++i) {
        cout << sortedTeam[i].name << " (" << sortedTeam[i].rating << " рейтинг)" << endl;
    }
}

// Функція для оновлення статистики гравця
void updatePlayerStats(vector<Player>& team, const string& name, int goals, int matches, double rating) {
    for (auto& player : team) {
        if (player.name == name) {
            player.goals = goals;
            player.matches = matches;
            player.rating = rating;
            cout << "Статистика гравця \"" << name << "\" оновлена." << endl;
            return;
        }
    }
    cout << "Гравця з ім'ям \"" << name << "\" не знайдено." << endl;
}

// Головна функція
int main() {
    vector<Player> team;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Додати гравця\n";
        cout << "2. Вивести список гравців\n";
        cout << "3. Пошук гравців за позицією\n";
        cout << "4. Підрахувати загальну кількість голів\n";
        cout << "5. Знайти найкращого бомбардира\n";
        cout << "6. Знайти гравця з найвищим рейтингом\n";
        cout << "7. Вибрати оптимальний склад\n";
        cout << "8. Оновити статистику гравця\n";
        cout << "9. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, position;
                int goals, matches;
                double rating;
                cout << "Введіть ім'я гравця: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введіть позицію гравця: ";
                getline(cin, position);
                cout << "Введіть кількість голів: ";
                cin >> goals;
                cout << "Введіть кількість матчів: ";
                cin >> matches;
                cout << "Введіть рейтинг: ";
                cin >> rating;
                addPlayer(team, name, position, goals, matches, rating);
                break;
            }
            case 2:
                displayPlayers(team);
                break;
            case 3: {
                string position;
                cout << "Введіть позицію для пошуку: ";
                cin.ignore();
                getline(cin, position);
                searchPlayersByPosition(team, position);
                break;
            }
            case 4:
                cout << "Загальна кількість голів: " << totalGoals(team) << endl;
                break;
            case 5:
                findTopScorer(team);
                break;
            case 6:
                findTopRatedPlayer(team);
                break;
            case 7: {
                int maxPlayers;
                cout << "Введіть кількість гравців для складу: ";
                cin >> maxPlayers;
                selectBestTeam(team, maxPlayers);
                break;
            }
            case 8: {
                string name;
                int goals, matches;
                double rating;
                cout << "Введіть ім'я гравця для оновлення: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введіть нову кількість голів: ";
                cin >> goals;
                cout << "Введіть нову кількість матчів: ";
                cin >> matches;
                cout << "Введіть новий рейтинг: ";
                cin >> rating;
                updatePlayerStats(team, name, goals, matches, rating);
                break;
            }
            case 9:
                cout << "Програма завершена. До побачення!" << endl;
                break;
            default:
                cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 9);

    return 0;
}
