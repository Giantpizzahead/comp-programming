/*
ID: sunnyky1
LANG: JAVA
TASK: ttwo

Solution: Just simulate the whole thing, stopping at the 160,001th minute
(there's no way they'll meet after that long). No optimizations needed,
because the grid is only 10x10.

Runtime: O(160001 + N^2)
*/

import java.util.*;
import java.io.*;

public class ttwo {
    char[][] grid;
    Entity cow, john;
    int[] cx = new int[] {0, 1, 0, -1};
    int[] cy = new int[] {-1, 0, 1, 0};

    ttwo() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("ttwo.in"));
        // For easier implementation
        grid = new char[12][12];
        for (int i = 0; i < 12; i++) {
            grid[0][i] = '*';
            grid[11][i] = '*';
            grid[i][0] = '*';
            grid[i][11] = '*';
        }
        for (int y = 1; y < 11; y++) {
            String line = fin.readLine();
            for (int x = 1; x < 11; x++) {
                if (line.charAt(x-1) == 'C') cow = new Entity(x, y, 0);
                else if (line.charAt(x-1) == 'F') john = new Entity(x, y, 0);
                else {
                    grid[y][x] = line.charAt(x-1);
                    continue;
                }
                grid[y][x] = '.';
            }
        }
        fin.close();

        int answer = simulate();
        PrintWriter fout = new PrintWriter("ttwo.out");
        fout.println(answer);
        fout.close();
    }

    int simulate() {
        int time = 1;
        int nx, ny;
        for (; time < 160002; time++) {
            // Move cow
            nx = cow.x + cx[cow.d];
            ny = cow.y + cy[cow.d];
            if (grid[ny][nx] == '*') cow.turn();
            else {
                cow.x = nx;
                cow.y = ny;
            }

            // Move john
            nx = john.x + cx[john.d];
            ny = john.y + cy[john.d];
            if (grid[ny][nx] == '*') john.turn();
            else {
                john.x = nx;
                john.y = ny;
            }

            // Check if intersect
            if (cow.x == john.x && cow.y == john.y) break;
        }
        return (time == 160002) ? 0 : time;
    }

    public static void main(String[] args) throws IOException {
        new ttwo();
    }
}

class Entity {
    int x, y, d;
    Entity(int x, int y, int d) {
        this.x = x;
        this.y = y;
        this.d = d;
    }
    void turn() {
        d = (d + 1) % 4;
    }
}