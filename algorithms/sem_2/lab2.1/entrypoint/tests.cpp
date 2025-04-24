#include <iostream>
#include <fstream>
#include <sstream> 
#include <random>
#include <unordered_map>
#include <algorithm>
#include <deque> 

#include "C:/Users/artem/Desktop/labs/algoritms/lab1/rbtree.cpp"

using namespace std; 

void read_test(unordered_map<std::string, RBTree> &genresTrees) {
    std::vector<std::string> genresTags = {"Биографии", "Комедии", "Ужасы", "Исторические", "Детские",
        "Приключения", "Короткометражки", "Анимация", "Мультфильмы",
        "Криминал", "Военные", "Фантастика", "Игры", "Семейные",
        "Документальные", "Драмы", "Спортивные", "Вестерны", "Музыкальные",
        "Фильмы-нуар", "Мелодрамы", "Реальное ТВ", "Триллеры", "Боевики",
        "Детективы", "Мюзиклы", "Фэнтези"};

    std::ifstream infile("C:/Users/artem/Desktop/labs/algoritms/lab1/entrypoint/films.csv");
    if (!infile.is_open()) {
        std::cout << "Error opening films.csv file.\n";
        return;
    }

    std::string line;
    std::getline(infile, line); // Header ignore

    while (std::getline(infile, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string film_name, ratingStr, genre;
        double rating;

        if (std::getline(iss, film_name, ';') &&
            std::getline(iss, ratingStr, ';') &&
            std::getline(iss, genre)) {

            try {
                // genre.erase(std::remove(genre.begin(), genre.end(), "\r"), genre.end());
                genre.erase(std::remove(genre.begin(), genre.end(), '\r'), genre.end());
                rating = std::stod(ratingStr);
                genresTrees.at(genre).insert(film_name, rating);
            } catch (const std::invalid_argument &e) {
                std::cout << "Invalid rating value: " << ratingStr << " in line: " << line << "\n";
                continue;
            } catch (const std::out_of_range &e) {
                std::cout << "Unknow genre: " << genre << "\n";
            } 
        } else {
            std::cout << "Invalid line format: " << line << "\n";
        }
    }

    infile.close();

    return;
}

bool check_structur_RB_tree(unordered_map<std::string, RBTree> &genresTrees, string tag) {
    int amt_B_node = 0;
    deque<pair<Node*, int>> dq;
    Node* root = genresTrees.at(tag).get_root();
    dq.push_back(make_pair(root, 0));
    string last_key = "";
    int last_count_B_node = 0;

    while (!dq.empty()) {
        Node *x = dq.front().first;
        int count_B_node = dq.front().second;
        dq.pop_front();
        
        if (count_B_node == -1) {
            last_key = "";
            last_count_B_node = dq.front().second;
            dq.push_back(make_pair(nullptr, -1));
            continue;
        }

        if (x != nullptr) {
            if (last_key > x->film_name || last_count_B_node != count_B_node) {
                return false;
            }

            if (x->color == BLACK) {
                count_B_node += 1;
                continue;
            }
            else if (x->right->color != BLACK || x->left->color != BLACK) {
                return false; 
            }
            else {
                dq.push_back(make_pair(x->left, count_B_node));
                dq.push_back(make_pair(x->right, count_B_node));
            }
        }
        else {
            if (amt_B_node == 0) {
                amt_B_node = count_B_node;
                continue;
            }
            else if (amt_B_node != count_B_node) {
                return false;
            }
        }
    }

    return true;
}

std::pair<std::string, int> generateRandomPair(int length = 10, int minNum = 1, int maxNum = 10) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string randomStr;
    srand(time(0));
    
    for (int i = 0; i < length; ++i) {
        randomStr += chars[rand() % chars.size()];
    }
    
    int randomNum = minNum + rand() % (maxNum - minNum + 1);
    return {randomStr, randomNum};
}

int main() {
    std::vector<std::string> genresTags = {"Биографии", "Комедии", "Ужасы", "Исторические", "Детские",
        "Приключения", "Короткометражки", "Анимация", "Мультфильмы",
        "Криминал", "Военные", "Фантастика", "Игры", "Семейные",
        "Документальные", "Драмы", "Спортивные", "Вестерны", "Музыкальные",
        "Фильмы-нуар", "Мелодрамы", "Реальное ТВ", "Триллеры", "Боевики",
        "Детективы", "Мюзиклы", "Фэнтези"};

    std::unordered_map<std::string, RBTree> genresTrees;
    for (const auto& genre : genresTags) {
        genresTrees[genre] = RBTree();
    }

    read_test(genresTrees);

    pair<string, int> rd_node = generateRandomPair();
    genresTrees.at(genresTags[0]).insert(rd_node.first, rd_node.second);
    cout << check_structur_RB_tree(genresTrees, genresTags[0]) << endl;

    cout << genresTrees.at(genresTags[0]).search(rd_node.first)->film_name << endl;

    cout << genresTrees.at(genresTags[0]).recommend(rd_node.second)->film_name << endl;
}