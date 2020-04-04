/*
ID: sunnyky1
LANG: JAVA
TASK: maze1

Solution: BFS from both exits at once, keeping track of the minimum number of steps
to get out of the maze at every cell. Output the max of all these steps. To make
implementation easier, divide the distance by 2 at the end to keep from having to
change the input format.

Runtime: O(4WH)
*/

import java.util.*;
import java.io.*;

public class maze1 {
    int W, H;
    ArrayList<Point> exits;
    char[][] maze;

    maze1() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("maze1.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        W = Integer.parseInt(st.nextToken()) * 2 + 1;
        H = Integer.parseInt(st.nextToken()) * 2 + 1;
        maze = new char[H][];
        for (int y = 0; y < H; y++) {
            maze[y] = fin.readLine().toCharArray();
        }

        // Find the 2 exits
        exits = new ArrayList<>(2);
        for (int i = 0; i < W; i++) {
            if (maze[0][i] == ' ') exits.add(new Point(i, 0));
            if (maze[H-1][i] == ' ') exits.add(new Point(i, H-1));
        }
        for (int i = 0; i < H; i++) {
            if (maze[i][0] == ' ') exits.add(new Point(0, i));
            if (maze[i][W-1] == ' ') exits.add(new Point(W-1, i));
        }

        int answer = bfs();
        PrintWriter fout = new PrintWriter("maze1.out");
        fout.println(answer);
        fout.close();
    }

    int bfs() {
        boolean[][] visited = new boolean[H][W];
        int currSteps = 1, currNum = 2, nextNum = 0;
        Queue<Point> q = new LinkedList<>();
        for (Point p : exits) {
            visited[p.y][p.x] = true;
            q.add(p);
        }

        Point c;
        int[] cx = new int[] {0, 1, 0, -1};
        int[] cy = new int[] {-1, 0, 1, 0};
        while (!q.isEmpty()) {
            c = q.poll();
            if (currNum == 0) {
                currNum = nextNum;
                nextNum = 0;
                currSteps++;
            }
            currNum--;

            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (inBounds(nx, ny) && maze[ny][nx] == ' ' && !visited[ny][nx]) {
                    visited[ny][nx] = true;
                    q.add(new Point(nx, ny));
                    nextNum++;
                }
            }
        }

        return currSteps / 2;
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < W && y >= 0 && y < H;
    }

    public static void main(String[] args) throws IOException {
        new maze1();
    }

    class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}