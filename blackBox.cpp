#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>

//Чёрный ящик организован наподобие примитивной базы данных. Он может хранить набор целых чисел и имеет выделенную переменную i. В начальный момент времени чёрный ящик пуст, 
//а значение переменной i равно нулю. Чёрный ящик обрабатывает последовательность поступающих команд (запросов). Существуют два вида запросов:
//Добавить(x) — положить в чёрный ящик элемент x;
//Получить() — увеличить значение переменной i на 1 и выдать копию i-го по величине элемента чёрного ящика (напомним, что i-м по величине элементом называется число, 
//стоящее на i-м месте в отсортированной по неубыванию последовательности элементов чёрного ящика).
//Необходимо разработать алгоритм, обрабатывающий заданную последовательность поступающих команд (запросов) за время O(m ⋅ logm), где m — число запросов Добавить.

std::vector <long long> max_heap;
std::vector<long long> min_heap;

void insert_min(long long x) {
	min_heap.push_back(x);
	long long i = min_heap.size() - 1;
	while (i > 0) {
		long long j = (i - 1) / 2;
		if (min_heap[j] <= min_heap[i]) {
			break;
		}
		else {
			long long k = min_heap[i];
			min_heap[i] = min_heap[j];
			min_heap[j]=k;
			i = j;
		}
	}
}

void extract_min() {
	min_heap[0] = min_heap[min_heap.size() - 1];
	min_heap.pop_back();
	long long i = 0;
	long long j;
	while (2 * i + 1 < min_heap.size()) {
		if ((2 * i + 2 == min_heap.size() || min_heap[2 * i + 1] < min_heap[2 * i + 2])) {
			j = 2 * i + 1;
		}
		else {
			j = 2 * i + 2;
		}

		if (min_heap[i] <= min_heap[j]) {
			break;
		}
		long long k = min_heap[i];
		min_heap[i] = min_heap[j];
		min_heap[j] = k;
		i = j;
	}
}

void insert_max(long long x) {
	max_heap.push_back(x);
	long long i = max_heap.size() - 1;
	while (i > 0) {
		long long j = (i - 1) / 2;
		if (max_heap[j] >= max_heap[i]) {
			break;
		}
		else {
			long long k = max_heap[i];
			max_heap[i] = max_heap[j];
			max_heap[j] = k;
			i = j;
		}
	}
}

void extract_max() {
	max_heap[0] = max_heap[max_heap.size() - 1];
	max_heap.pop_back();
	long long i = 0;
	long long j;
	while (2 * i + 1 < max_heap.size()) {
		if ((2 * i + 2 == max_heap.size() || max_heap[2 * i + 1] > max_heap[2 * i + 2])) {
			j = 2 * i + 1;
		}
		else {
			j = 2 * i + 2;
		}
		if (max_heap[i] >= max_heap[j]) {
			break;
		}
		long long k = max_heap[i];
		max_heap[i] = max_heap[j];
		max_heap[j] = k;
		i = j;
	}
}

int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	long long m;			// Добавить
	long long n;			// Получить
	in >> m;
	in >> n;

	std::vector<long long> vec(m);
	for (long long j = 0; j < m; j++) {        //Добавить
		in >>vec[j];
	}

	std::vector<long long> pol(n);				//Получить
	for (long long j = 0; j < n; j++) {
		in >> pol[j];
	}

	long long p1 = 0;
	for (long long i = 0; i < n; i++) {
		long long p = pol[i];		//     получить
		while (p > min_heap.size() + max_heap.size()) {
			if (!max_heap.empty() && max_heap[0] > vec[p1]) {
				insert_min(max_heap[0]);
				extract_max();
				insert_max(vec[p1]);
				p1++;
			}
			else {
				insert_min(vec[p1]);			// 
				p1++;
			}
		}
		if (p == min_heap.size() + max_heap.size()) {
			out << min_heap[0] << " ";
			//взять мин 0 и перенести в макс
			if (i == n - 1) {
				break;
			}
			else {
				insert_max(min_heap[0]);
				extract_min();
			}
		}
	}

	in.close();
	out.close();
	return 0;
}
