#include <sstream>
#include <string>
#include <cmath>
#include <limits>

enum Color {
    RED,
    BLACK
};

struct Node {
    std::string film_name;
    double sum_ratings;
    double avg_rating;
    int count_ratings;

    Color color;
    Node *left, *right, *parent;

    Node(const std::string &name, double rating)
        : film_name(name), sum_ratings(rating), avg_rating(rating), count_ratings(1),
        color(RED), left(nullptr), right(nullptr), parent(nullptr) {
    }

    /**
     * Обновить значение рейтиинга.
     * 
     * @note При добавлении новой оценки к фильму:
     * 
        - Обновите сумму оценок и увеличьте количество оценок.

        - Пересчитайте среднюю оценку.
        Если текущая средняя оценка равна `avg`,
        количество оценок равно `n`,
        а новая оценка равна `r`,
        то новое значение средней оценки вычисляется по формуле:  
            
        `новое среднее = ((avg × n) + r) / (n + 1)`
     
     */
    void updateRating(double newRating) {
        sum_ratings += newRating;
        count_ratings++;
        avg_rating = ((avg_rating * (count_ratings - 1)) + newRating) / (count_ratings);
    }
};


class RBTree {
public:
    Node *root;

    RBTree() : root(nullptr) {}

    /**
     * Левое вращение вокруг узла x.
     * 
     * @param x нода, вокруг которой будет выполняться вращение
     */

    Node *get_root() {
        return root;
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            this->root = y;
        } 
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    /**
     * Правок вращение вокруг узла x.
     * 
     * @param x нода, вокруг которой будет выполняться вращение
     */
    void rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nullptr) {
            this->root = x;
        }
        else if (y == y->parent->right) {
            y->parent->right = x;
        }
        else {
            y->parent->left = x;
        }

        x->right = y;
        y->parent = x;
    }

    /**
     * Вставить/обновить фильм и рейтинг
     * 
     * @param film_name название фильма
     * @param rating рейтинг
     */
    void insert(const std::string &film_name, double rating) {
        Node *nw_node = new Node(film_name, rating);
        Node *cur = root;  
        Node *pt_nw_node = nullptr;

        while (cur != nullptr) {
            pt_nw_node = cur;

            if (cur->film_name == film_name) {
                cur->updateRating(rating);
                return;
            }
            if (nw_node->film_name < cur->film_name) {
                cur = cur->left;
            } 
            else {
                cur = cur->right;
            }
        }

        nw_node->parent = pt_nw_node;

        if(pt_nw_node == nullptr) {
            this->root = nw_node;
        }
        else if(nw_node->film_name < pt_nw_node->film_name) {
            pt_nw_node->left = nw_node;
        }
        else {
            pt_nw_node->right = nw_node;
        }

        nw_node->left = nullptr;
        nw_node->right = nullptr;
        nw_node->color = RED;

        fixInsert(nw_node);
    }

    /**
     * Восстановить свойства красно-черного дерева после вставки.
     * 
     * @param node вставленный узел, который нужно исправить
     */
    void fixInsert(Node *node) {
       if (node == this->root) {
           this->root->color = BLACK;
           return;
       } 

       while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node *uncle = node->parent->parent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent; 
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED; 
                    rightRotate(node->parent->parent);
                }
            }
            else {
                Node *uncle = node->parent->parent->left;

                if(uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if(node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }

            if(node == this->root) {
                break;
            }
        }

        this->root->color = BLACK;
    }    

    /**
     * Найти фильм по названию
     * 
     * @param film_name название фильма
     * 
     * @return указатель на ноду, содержащий фильм. nullptr если не найдено.
     */
    Node *search(const std::string &film_name) {
        Node *x = this->root;

        while (x != nullptr){
            if(x->film_name == film_name) {
                return x;
            }

            if(x->film_name > film_name) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        return nullptr;
    }

    /**
     * Обход по порядку для поиска узла со средним рейтингом, наиболее близким к target_rating.
     * 
     * @param node
     * @param target_rating таргетный рейтинг
     * 
     * @param bestMatch наиболее подходящий узел, найденный на данный момент. 
     * @param bestDiff наименьшая разница между целевым и фактическим рейтингами, найденными на данный момент.
     */
    void inOrderRecommend(Node *node, double target_rating, Node *&bestMatch, double &bestDiff) {
        if (node != nullptr) {
            double diff = target_rating - node->avg_rating;
            if (diff < 0) {
                diff *= -1;
            }

            if(diff < bestDiff) {
                bestDiff = diff;
                bestMatch = node;
            }
            inOrderRecommend(node->left, target_rating, bestMatch, bestDiff);
            inOrderRecommend(node->right, target_rating, bestMatch, bestDiff); 
        }
    }

    /**
     * Получить рекомендацию — фильм со средним рейтингом, наиболее близким к target_rating.
     * 
     * @param target_rating таргет тейтинг
     * 
     * @return нода на лучшее совпадение. если не найдено - nullptr
     */
    Node *recommend(double target_rating) {
        Node *node = this->root;
        Node *bestMatch = nullptr;
        double bestDiff = 1e10;

        inOrderRecommend(node, target_rating, bestMatch, bestDiff);
        return bestMatch;
    }
};
