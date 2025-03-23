#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct City {
    int id;
    int degree;
    int color;
};

// So sánh để sắp xếp theo bậc giảm dần
bool compareByDegree(const City& a, const City& b) {
    return a.degree > b.degree;
}

void WelchPowell(vector<vector<int>>& graph, int n) {
    // Tạo danh sách các thành phố với bậc của chúng
    vector<City> cities(n);
    for (int i = 0; i < n; i++) {
        cities[i].id = i;
        cities[i].color = -1;
        cities[i].degree = 0;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1) {
                cities[i].degree++;
            }
        }
    }

    // Sắp xếp các thành phố theo bậc giảm dần
    sort(cities.begin(), cities.end(), compareByDegree);

    // Tô màu đỉnh đầu tiên
    int currentColor = 0;
    cities[0].color = currentColor;

    // Tô màu các đỉnh còn lại
    while (true) {
        bool allColored = true;
        // Kiểm tra xem còn đỉnh nào chưa được tô màu không
        for (int i = 0; i < n; i++) {
            if (cities[i].color == -1) {
                allColored = false;
                break;
            }
        }
        if (allColored) break;

        currentColor++;
        for (int i = 0; i < n; i++) {
            if (cities[i].color != -1) continue;

            bool canColor = true;
            // Kiểm tra các đỉnh kề
            for (int j = 0; j < n; j++) {
                if (graph[cities[i].id][j] == 1) {
                    // Tìm màu của đỉnh j trong danh sách cities
                    for (const City& city : cities) {
                        if (city.id == j && city.color == currentColor) {
                            canColor = false;
                            break;
                        }
                    }
                }
            }
            if (canColor) {
                cities[i].color = currentColor;
            }
        }
    }

    // In kết quả
    cout << "Ket qua to mau:" << endl;
    for (const City& city : cities) {
        cout << "Thanh pho " << city.id + 1 << ": Mau " << city.color + 1 << endl;
    }
    cout << "So mau su dung: " << currentColor + 1 << endl;
}

int main() {
    ifstream fin("color3.txt");
    int n;
    fin >> n;
    
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> graph[i][j];
        }
    }
    
    WelchPowell(graph, n);
    return 0;
}
