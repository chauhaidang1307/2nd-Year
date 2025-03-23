#include <iostream>
#include <vector>
using namespace std;

struct Vertices {
    int Dinh;
    int Degrees;
    int color;
    vector<int> Ke;
    vector<int> colorBan;
    bool able;

    // Constructor:
    Vertices() : Dinh(0), Degrees(0), color(0), able(true) {}
    Vertices(int Dinh, int degrees) : Dinh(Dinh), Degrees(degrees), able(true), color(0) {}
};

int highestDeg(vector<Vertices>& Graph) { // Truyền vào tham chiếu để không sao chép
    int max = 1;
    for (int i = 2; i <= Graph.size() - 1; i++) {
        if (Graph[max].Degrees < Graph[i].Degrees) {
            max = i;
        }
    }
    return max;
}

void Dsatur(const char* fileName) {
    int n;
    freopen(fileName, "r", stdin);
    cin >> n;
    int temp;
    vector<Vertices> Graph(n + 1);

    //Input các dữ liệu vào biến struct vừa tạo từ file
    for (int i = 1; i <= n; i++) {
        Graph[i] = Vertices(i, 0);
        for (int j = 1; j <= n; j++) {
            cin >> temp;
            if (temp == 1) {
                Graph[i].Degrees++;
                Graph[i].Ke.push_back(j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int max = highestDeg(Graph);
        if (Graph[max].Degrees != 0) {
            int color = 1;

            while (true) { //Tìm màu không bị cấm để gán cho đỉnh
                bool found = false;
                for (int k = 0; k < Graph[max].colorBan.size(); k++) {
                    if (Graph[max].colorBan[k] == color) {
                        found = true;
                        break;
                    }
                }
                if (!found) break;
                color++;
            }

            // Gán màu và cập nhật bậc
            Graph[max].color = color;
            Graph[max].Degrees = 0;
            Graph[max].able = false;
            Graph[max].colorBan.push_back(color);

            // Cập nhật các đỉnh kề
            for (int j = 0; j < Graph[max].Ke.size(); j++) {
                int temp = Graph[max].Ke[j];
                if (Graph[temp].able) {
                    Graph[temp].Degrees--;
                    Graph[temp].colorBan.push_back(color);
                }
            }
        }
    }

    // Gán màu cho các đỉnh chưa được gán màu
    for (int i = 1; i <= n; i++) {
        if (Graph[i].able) {
            int color = 1;
            while (true) { //Tìm màu chưa được sử dụng hoặc không bị cấm
                bool found = false;
                for (int k = 0; k < Graph[i].colorBan.size(); k++) {
                    if (Graph[i].colorBan[k] == color) {
                        found = true;
                        break;
                    }
                }
                if (!found) break;
                color++;
            }
            Graph[i].color = color;
        }
    }

    // Xuất kết quả
    for (int i = 1; i <= n; i++) {
        cout << "Dinh: " << Graph[i].Dinh << " Bac: " << Graph[i].Degrees << " Color: " << Graph[i].color << endl;
        cout << "Dinh ke: ";
        for (int j = 0; j < Graph[i].Ke.size(); j++) {
            cout << Graph[i].Ke[j] << " ";
        }
        cout << endl;
    }

    // Tìm số màu sử dụng
    int maxColor = Graph[1].color;
    for (int i = 2; i <= n; i++) {
        if (Graph[i].color > maxColor) {
            maxColor = Graph[i].color;
        }
    }
    cout << "So mau su dung: " << maxColor << endl;
}

int main() {
    Dsatur("color2.txt");
    return 0;
}