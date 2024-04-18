//Задача 42. Лента
//Задана лента шириной в одну клетку и длиной в n клеток.На каждой клетке написано некоторое целое число.
//Играют два игрока, которые ходят поочерёдно.За один ход игрок отрезает от ленты одну из крайних клеток и забирает её.
//Игра останавливается, когда лента заканчивается.Выигрыш игрока равен сумме чисел на находящихся у него клетках ленты.
//Необходимо определить величину выигрыша, которую может себе гарантировать игрок, начинающий игру первым.
//(Это тот размер выигрыша, который первый игрок обеспечит себе при любой игре второго игрока.)
#include<iostream>
#include <fstream>
#include <algorithm>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::ifstream in("input.txt");
	int n;
	in >> n;
	//std::cin >> n;
	std::vector<int> vec(n + 1);
	vec[0] = 0;
	std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(n + 1, -1));
	std::vector<int> vecsum(n + 1);
	vecsum[0] = 0;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int x;
		in >> x;
		//std::cin >> x;
		vec[i + 1] = x;
		matrix[i + 1][i + 1] = x;
		sum = sum + x;
		vecsum[i + 1] = (sum);
	}
	in.close();

	std::ofstream out;
	out.open("output.txt");
	int res = 0;
	if (n == 1) {
		res = vec[1];
	}
	else if (n == 2) {
		res = std::max(vec[1], vec[2]);
	}
	else {
		int perem = (n - 1);

		while (perem > 0) {
			for (int i = 1; i < n; i++) {
				for (int j = i + 1; j < n + 1; j++) {
					if (matrix[i][j] != -1) {
						continue;
					}
					else if (matrix[i][j] == -1) {
						if (matrix[1 + i][j] == -1 || matrix[i][j - 1] == -1) {
							break;
						}
						else {
							int sum = vecsum[j] - vecsum[i - 1];
							int r = sum - std::min(matrix[1 + i][j], matrix[i][j - 1]);
							matrix[i][j] = r;
						}
					}
				}
			}
			perem--;
		}

		res = matrix[1][n];
	}

	out << res;
	out.close();

	return 0;
}
