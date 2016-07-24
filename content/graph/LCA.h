/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2015-09-20
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Lowest common ancestor. Finds the lowest common
 * ancestor in a tree (with 0 as root). C should be an adjacency list of the tree,
 * either directed or undirected.
 * Can also find the distance between two nodes.
 * Usage:
 *  LCA lca(undirGraph);
 *  lca.query(firstNode, secondNode);
 *  lca.distance(firstNode, secondNode);
 * Time: $O(|V| \log |V| + Q)$
 */

#pragma once

#include <vector>

using namespace std;

typedef vector<pii> vpi;
typedef vector<vpi> graph;
const pii inf(1 << 29, -1);

#define RMQ_HAVE_INF /** exclude-line */
#include "../data-structures/RMQ.h"

struct LCA {
	vi time;
	vector<ll> dist;
	RMQ<pii> rmq;

	LCA(graph& C) : time(sz(C), -99), dist(sz(C)), rmq(dfs(C)) {}

	vpi dfs(graph& C) {
		vector<tuple<int, int, int, ll> > q(1);
		vpi ret;
		int T = 0, v, p, d; ll di;
		while (!q.empty()) {
			tie(v, p, d, di) = q.back();
			q.pop_back();
			if (d) ret.emplace_back(d, p);
			time[v] = T++;
			dist[v] = di;
			trav(e, C[v]) if (e.first != p)
				q.emplace_back(e.first, v, d+1, di + e.second);
		}
		return ret;
	}

	int query(int a, int b) {
		if (a == b) return a;
		a = time[a], b = time[b];
		return rmq.query(min(a, b), max(a, b)).second;
	}

	ll distance(int a, int b) {
		int lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};
