//6 9
//0 1 5
//0 3 19
//0 4 6
//1 2 10
//2 3 13
//1 4 1
//1 5 9
//3 5 8
//4 5 2

#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> map; //массив хранит веса дорог
vector<int> road; //номера узлов текущей "дороги"
vector<bool> incl; //true, если i-ая вершина включена в путь
vector<int> way; //искомый самый короткий путь
int waylen; //его длина
int start, finish; //начальная и конечная вершины
bool found;
int len; //найденный "вес" маршрута
int c_len; //текущий "вес" маршрута

void step(int s, int f, int p) { //рекурсивный поиск шага пути
    int c; //номер вершины, кудв делаем шаг
    if (s == f) { //путь найден
        found = true;
        len = c_len; //запоминаем общий вес пути
        waylen = p; //запоминаем длину пути (количесвто узлов)
        for (int i = 0; i < waylen; i++) way[i] = road[i]; //запоминаем сам путь
    }
    else { //выбор очередной точки
        for (c = 0; c < N; c++) { //проверяем все вершины
            int w = map[s][c];
            if (w && !incl[c] && (len == 0 || c_len + w < len)) {
                road[p] = c; //включаем точку в путь
                incl[c] = true; //пометить как включенную
                c_len += w; //учесть в общем весе пути
                step(c, f, p + 1); //вызвать себя для поиска следующей точки
                road[p] = 0; //вернуть как было
                incl[c] = false;
                c_len -= w;
            }
        }
    }
}

int main() {
    system("chcp 65001");
    setlocale(LC_ALL, "RU");

    int a, b, c;

    cout << "Введите количество городов: " << endl;
    cin >> N;
    cout << "Введите количество дорог: " << endl;
    cin >> M;

    map.resize(N, vector<int>(N, 0));
    road.resize(N);
    incl.resize(N);
    way.resize(N);

    for (int i = 0; i < M; i++) {
        cout << "Введите a,b,c, где a-город где начинается дорога, b-куда ведет дорога, c-вес дороги(нумерация с 0): " << endl;
        cin >> a >> b >> c;
        map[a][b] = c;
        map[b][a] = c;
    }

    cout << "Введите начало и конец пути через пробел: " << endl;
    cin >> start >> finish;

    road[0] = start; //первую точку внесли в маршрут
    incl[start] = true; //и пометики как включенную
    found = false; //но путь пока не найден
    step(start, finish, 1); //ищем вторую точку

    if (found) {
        cout << "Путь: ";
        for (int i = 0; i < waylen; i++) cout << " -> " << way[i];
        cout << endl << "Его длина: " << len;
    }
    else cout << "Путь не найден!" << endl;

    return 0;
}
