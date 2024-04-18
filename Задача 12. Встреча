//В городе N домиков и M дорог.В каждом домике живёт по одному человеку.
//Необходимо найти точку(место встречи всех людей), от которой суммарное расстояние по дорогам до всех домиков будет минимальным.
//Место встречи следует искать среди точек, в которых расположены домики, 
//а также точек, лежащих на дороге и отстоящих от домиков на целое число единиц длины.

// q.enqueue(start) = q.push(start);
// v = q.dequeue()  = int v = q.front(); q.pop();

#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
#include <queue>

std::vector<long long>processed;
std::vector<long long>dist;
std::vector<std::vector<std::pair<long long, long long>>> a;

void distances(long long start) {

	typedef std::pair<long long, long long> QueueItem;
	std::priority_queue <QueueItem, std::vector<QueueItem>, std::greater<QueueItem> > q;
	q.push({ 0, start });

	while (!q.empty()) {
		std::pair<long long, long long> c = q.top();
		q.pop();
		long long dv = c.first;
		long long v = c.second;

		if (processed[v]) {
			continue;
		}

		processed[v] = true;
		dist[v] = dv;

		for (std::pair<long long, long long> e : a[v]) {
			long long u = e.first;
			long long cu = e.second;
			if (!processed[u] && dv + cu < dist[u]) {
				q.push({ dv + cu,u });
			}
		}
	}
}

int main() {
	std::ifstream in("input.in");
	std::ofstream out("output.out");
	/*std::ifstream in("input.txt");
	std::ofstream out("output.txt");*/
	long long n;
	long long m;
	in >> n >> m;
	if (n == 2) {
		long long u, v, w;
		in >> u >> v >> w;
		out << u << " "<< v << " " << w / 2;
	}
	else {
		std::vector<std::vector<std::pair<long long, long long>>> a1(n);
		a = a1;
		for (long long i = 0; i < m; i++) {
			long long u, v, w;
			in >> u >> v >> w;
			a[u - 1].push_back(std::make_pair(v - 1, w));
			a[v - 1].push_back(std::make_pair(u - 1, w));
		}

		std::vector<long long>result(n, 0);

		for (int i = 0; i < n; i++) {
			long long start = i;

			std::vector<long long>processed1(n, false);
			std::vector<long long>dist1(n, LLONG_MAX);
			processed = processed1;
			dist = dist1;
			dist[start] = 0;
			distances(start);
			for (int j = 0; j < n; j++) {
				result[i] += dist[j];
			}
		}
		std::vector<long long>::iterator res = std::min_element(result.begin(), result.end());
		out << std::distance(result.begin(), res) + 1 << " " << *res;
	}

	in.close();
	out.close();
	return 0;
}

