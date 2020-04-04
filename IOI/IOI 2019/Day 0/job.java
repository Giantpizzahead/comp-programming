import java.util.*;

@SuppressWarnings("unchecked")
class job {
	int N;
	int[] outEdges, p, u, d;
	ArrayList<Integer>[] c;
	Pair[] priority;
	long time, answer;

	public long scheduling_cost(int[] p, int[] u, int[] d) {
		N = p.length;
		this.p = p;
		this.u = u;
		this.d = d;
		outEdges = new int[N];
		c = new ArrayList[N];
		for (int i = 0; i < N; i++) c[i] = new ArrayList<>(2);

		// Which subtask is it?
		for (int i = 1; i < N; i++) {
			outEdges[p[i]]++;
			c[p[i]].add(i);
		}

		int maxNot0 = 0;
		for (int i = 1; i < N; i++) {
			if (outEdges[i] != 0) {
				maxNot0 = Math.max(outEdges[i], maxNot0);
			}
		}

		if (maxNot0 == 0) {
			// Subtasks 2 & 3
			return solveOnly0();
		} else if (maxNot0 == 1 && outEdges[0] == 1) {
			// Subtask 1
			return solveLinear();
		} else if (maxNot0 == 1 && outEdges[0] <= 2) {
			// Subtask 4
			// return solveDP();
			return solveNSquared();
		} else {
			// Subtask 5
			return solveNSquared();
		}
	}

	long solveOnly0() {
		// Eval in order of decrasing U/D
		priority = new Pair[N - 1];
		for (int i = 1; i < N; i++) {
			priority[i-1] = new Pair(i, (double) u[i] / d[i]);
		}
		Arrays.sort(priority, new Comparator<Pair>() {
			@Override
			public int compare(Pair o1, Pair o2) {
				double res = o2.p - o1.p;
				if (res < 0) return -1;
				else if (res > 0) return 1;
				else return 0;
			}
		});

		time = d[0];
		answer = d[0] * u[0];
		Pair p;
		for (int i = 0; i < N - 1; i++) {
			p = priority[i];
			time += d[p.i];
			answer += time * u[p.i];
		}
		return answer;
	}

	long solveLinear() {
		time = 0;
		answer = 0;
		int curr = 0;
		while (true) {
			time += d[curr];
			answer += time * u[curr];
			if (c[curr].size() == 0) break;
			else curr = c[curr].get(0);
		}
		return answer;
	}

	double[] pri;
	boolean[] used;
	int usedCount = 0;
	long solveNSquared() {
		time = 0;
		answer = 0;
		used = new boolean[N];
		while (usedCount < N) {
			pri = new double[N];
			getPriorities(0, time, 0);
			// Find max priority node & use all nodes leading up to it
			double cmax = -1;
			int maxi = -1;
			for (int i = 0; i < N; i++) {
				if (pri[i] > cmax) {
					cmax = pri[i];
					maxi = i;
				}
			}
			// Use this node
			// System.out.println(maxi);
			useNode(maxi);
		}
		return answer;
	}

	void getPriorities(int n, long ctime, long ccost) {
		if (used[n]) pri[n] = -1;
		else {
			ctime += d[n];
			ccost += ctime * u[n];
			pri[n] = (double) ccost / ctime / ctime;
		}
		for (int e : c[n]) getPriorities(e, ctime, ccost);
	}

	void useNode(int n) {
		if (n == -1) return;
		if (!used[n]) {
			// Use parent nodes first
			useNode(p[n]);
			time += d[n];
			answer += time * u[n];
			used[n] = true;
			usedCount++;
		}
	}

	static class Pair {
		int i;
		double p;
		Pair(int i, double p) {
			this.i = i;
			this.p = p;
		}
	}
}
