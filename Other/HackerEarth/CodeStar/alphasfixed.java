package CodeStar;/*
Solution: Dijkstra without a visited array.

Issue with my code: I checked if the Dijkstra reached a computer before checking if the
other reached computers might've given a shorter path to that computer. In other words,
I checked for computers at the wrong location; if the computers were arranged in a V shape,
my algorithm would fail, because instead of checking from the top-left to top-right, it
would mark both at once, using the distance from the bottom one.

So close to top 10... yet so far... :(
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class alphasfixed {
    int C, R, N;
    boolean[][] grid;
    State[] computers;
    HashMap<Integer, Integer> locToComputer;
    final int INF = 999999999;

    alphasfixed() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        C = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        grid = new boolean[R][C];
        computers = new State[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            computers[i] = new State(x, y, 0);
        }

        st = new StringTokenizer(in.readLine());
        int temp = Integer.parseInt(st.nextToken());
        for (int i = 0; i < temp; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            grid[y][x] = true;
        }
        in.close();

        locToComputer = new HashMap<>();
        for (int i = 0; i < N; i++) {
            locToComputer.put(hashCoord(computers[i].x, computers[i].y), i);
        }

        int answer = dijkstra();
        System.out.println(answer);
    }

    int dijkstra() {
        int[][] bestDist = new int[R][C];
        boolean[][] visited = new boolean[R][C];
        boolean[] visitedComps = new boolean[N];
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                bestDist[y][x] = INF;
                visited[y][x] = false;
            }
        }

        bestDist[computers[0].y][computers[0].x] = 0;
        visitedComps[0] = true;

        PriorityQueue<State> pq = new PriorityQueue<>(new Comparator<State>() {
            @Override
            public int compare(State a, State b) {
                return a.c - b.c;
            }
        });
        pq.add(new State(computers[0].x, computers[0].y, 0));
        int answer = 0;
        int numCompsVisited = 1;
        int[] cx = new int[] {0, 1, 0, -1};
        int[] cy = new int[] {1, 0, -1, 0};

        State curr;
        int x, y, c, nx, ny, nc;
        while (numCompsVisited != N) {
            curr = pq.poll();
            x = curr.x;
            y = curr.y;
            c = curr.c;

            if (visited[y][x]) continue;
            visited[y][x] = true;

            // Check if at target computer
            if (locToComputer.containsKey(hashCoord(x, y)) && !visitedComps[locToComputer.get(hashCoord(x, y))]) {
                // New computer found
                answer += c;
                numCompsVisited++;
                // System.out.println("Visited comp " + locToComputer.get(hashCoord(nx, ny)) + " with cost " + (c + 1));
                visitedComps[locToComputer.get(hashCoord(x, y))] = true;
                c = 0;
                bestDist[y][x] = 0;
            }

                // Check neighbors
            for (int i = 0; i < 4; i++) {
                nx = x + cx[i];
                ny = y + cy[i];
                if (valid(nx, ny)) {
                    nc = c + 1;
                    if (nc < bestDist[ny][nx]) {
                        // New best dist found; revisit
                        bestDist[ny][nx] = nc;
                        visited[ny][nx] = false;
                        pq.add(new State(nx, ny, nc));
                    }
                }
            }
        }

        return answer;
    }

    boolean valid(int x, int y) {
        return x >= 0 && x < C && y >= 0 && y < R && !grid[y][x];
    }

    int hashCoord(int x, int y) {
        return x * 201 + y;
    }

    public static void main(String[] args) throws IOException {
        new alphasfixed();
    }

    static class State {
        int x, y, c;
        State(int x, int y, int c) {
            this.x = x;
            this.y = y;
            this.c = c;
        }
    }
}
