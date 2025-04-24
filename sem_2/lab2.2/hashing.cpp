#include "MurmurHash3.cpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

/**
* Определение типов:
*   - FEATURE: вектор double для хранения признаков.
*   - LABEL: целочисленный тип для метки (0 или 1).
*   - целочисленная константа HASH_DIM (размерность хешированного пространства ).
*/

using FEATURE = vector<double>;
using LABEL = short int;
constexpr short int HASH_DIM = 1000; 

struct Sample {
    FEATURE features;
    LABEL label;
};

/**
 * Перевести текст в фичи
 * 
 * Каждый токен к нижнему регистру -> хеш от строки -> feats[index] += 1, где index = хеш % HASH_DIM
 * Затем выполнить L2-нормализацию feats.
 * 
 * @param text 
 * @return vec<double> feats
 * 
 * @solve  
 */

vector<double> text_to_features(const std::string& text) {
    vector<double> feats(HASH_DIM, 0);

    string low_text = text;
    transform(low_text.begin(), low_text.end(), low_text.begin(), ::tolower);

    istringstream iss(low_text);
    string word;
    while (iss >> word) {
        uint32_t hash = 0;
        MurmurHash3(&word, word.size(), 42, &hash);
        feats[hash % HASH_DIM] += 1;
    }

    double L2_norm = 0;
    for (double value : feats) {
        L2_norm += pow(value, 2);
    }
    L2_norm = sqrt(L2_norm);
    if (L2_norm != 0){
        for (double &value : feats) {
            value /= L2_norm;
        }
    }

    return feats;
}

// Можно использовать внешние источники, но обязательно укажите ссылку на них.
// Если источник = генеративные модели / не будет источников - будет больно на защите.
class LogisticRegression {
public:
    size_t dim = HASH_DIM;
    double lr = 0.2;
    double reg_lambda = 0.01;
    double class_weight_0 = 1.0;  // вес для класса 0 (ham)
    double class_weight_1 = 1.0;  // вес для класса 1 (spam)
    LogisticRegression()
    : weights(dim, 0.0),
      learning_rate(lr),
      lambda(reg_lambda),
      epochs(500) {}

    /**
     * Обучаем логрег.
     * 
     * @param vec<Sample> trainData - наши фичи : labels
     * @param vec<Sample> validData - на чем считаем метрики
     * 
     * тут набросок, можете предложить свой вариант реализации. 
     * например - вывод лосса на обучении, или каджые M эпох уменьшает lr
     * 
     * при указании источника спрашивать как работает не будем.
     * 
     * функция должна обновить weights
     * @solve
     */

    //Источник вдохновения: https://habr.com/ru/articles/864890/, https://en.wikipedia.org/wiki/Logistic_regression
    void train(const std::vector<Sample>& trainData, const std::vector<Sample>& validData) { 
        for (int epoch = 0; epoch < epochs; ++epoch) {
            vector<double> gradients(dim, 0.0);
            double loss = 0.0;

            for (const auto& sample : trainData) {
                double pred = sigmoid(dot_product(weights, sample.features));
                double error = pred - sample.label;
                if (pred == 0) {
                    pred += 1e-9;
                }else if (pred == 1) {
                    pred -= 1e-9;
                }
                loss += -sample.label * log(pred) - (1 - sample.label) * log(1 - pred);
                
                for (size_t i = 0; i < dim; ++i) {
                    gradients[i] += error * sample.features[i];
                }
            }
            
            loss /= trainData.size();
            for (size_t i = 0; i < dim; ++i) {
                weights[i] -= learning_rate * (gradients[i] / trainData.size() + lambda * weights[i]);
            }
            
            if (epoch % 50 == 0) {
                learning_rate *= 0.95;
            }
        }
    }

    /**
     * Предсказываем класс для новых фичей
     * 
     * должна вернуть vec<double> metrics = {0, 0, 0, 0}; // TP, TN, FP, FN 
     * @param data - vec<Sample> данные для валидации
     * @solve
     */
    std::vector<double> evaluate(const std::vector<Sample>& data) const {
        double TP = 0.0, TN = 0.0, FP = 0.0, FN = 0.0;

        for (const auto& sample : data) {
            int prediction = predict(sample.features);

            if (sample.label == 1 && prediction == 1) {
                TP += 1.0;
            } else if (sample.label == 0 && prediction == 0) {
                TN += 1.0;
            } else if (sample.label == 0 && prediction == 1) {
                FP += 1.0;
            } else if (sample.label == 1 && prediction == 0) {
                FN += 1.0;
            }
        }

        return {TP, TN, FP, FN};
    }

    int predict(const FEATURE& feats) const {
        return (sigmoid(dot_product(weights, feats)) >= 0.5) ? 1 : 0;
    }

private:
    std::vector<double> weights;
    double learning_rate;
    double lambda;
    int epochs;

    static double dot_product(const FEATURE& w, const FEATURE& x) {
        double res = 0.0;
        for (size_t i = 0; i < w.size(); ++i) {
            res += w[i] * x[i];
        }
        return res;
    }

    // можете использовать другую активацию
    static double sigmoid(double z) {
        return 1.0 / (1.0 + exp(-z));
    }
};

/**
 * Загрузить данные из csv
 * csv формата class,text
 * 
 * затем загруженные данные нужно пропустить через text_to_features
 * 
 * @param filename путь до файла, указывать как "entrypoiny/FILENAME"
 * @param vec<Sample> data - куда положить загруженные данные
 * @return bool если загрузка успешна
 * 
 * @solve  
 */
bool read_csv(const std::string& filename, std::vector<Sample>& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return false;
    }

    string line;
    while (std::getline(file, line)) {
        istringstream iss(line);
        string label, text;

        if (!(getline(iss, label, ',') && getline(iss, text))) {
            continue;
        }

        Sample sample;
        if (label == "ham") {
            sample.label = 0;
        } else if (label == "spam") {
            sample.label = 1;
        } else {
            continue;
        }

        sample.features = text_to_features(text);

        data.push_back(sample);
    }

    file.close();

    return true;
}
