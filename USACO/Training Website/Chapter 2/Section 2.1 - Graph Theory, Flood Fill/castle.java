/*
ID: sunnyky1
LANG: JAVA
TASK: castle

Solution: Floodfill to find all the rooms in the castle. Label each module with a
room ID representing what room the module is part of. Then, try removing every
inner edge (Max MN edges to try) by joining the two room IDs (skip if they're the
same), and seeing how big the resulting room is.

Runtime: O(MN)
*/

import java.util.*;
import java.io.*;

public class castle {
    int N, M, numRooms;
    ArrayList<Integer> roomSizes;
    int[][] walls, roomID;
    int[] cx = new int[] {-1, 0, 1, 0};
    int[] cy = new int[] {0, -1, 0, 1};
    int[] hasWall = new int[] {1, 1 << 1, 1 << 2, 1 << 3};

    castle() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        M = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        walls = new int[N][M];
        roomID = new int[N][M];
        for (int y = 0; y < N; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 0; x < M; x++) {
                walls[y][x] = Integer.parseInt(st.nextToken());
            }
        }
        fin.close();

        // Do floodfill
        int largestRoom = floodfill();

        // Try removing every wall
        int[] bestWall = removeWall();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("castle.out")));
        fout.println(numRooms);
        fout.println(largestRoom);
        fout.println(bestWall[0]);
        fout.println((bestWall[2] + 1) + " " + (bestWall[1] + 1) + " " + ((bestWall[3] == 0) ? "N" : "E"));
        fout.close();
    }

    int[] removeWall() {
        // Return is in format (new room size, x, y, 0 or 1 for N or E)
        int[] bestWall = new int[] {-1, -1, -1, -1};

        // Follow the order descried in the problem
        for (int x = 0; x < M; x++) {
            for (int y = N-1; y >= 0; y--) {
                // Remove top wall
                if (y != 0 && roomID[y][x] != roomID[y-1][x]) {
                    int newSize = roomSizes.get(roomID[y][x]) + roomSizes.get(roomID[y-1][x]);
                    if (newSize > bestWall[0]) {
                        // New best
                        bestWall = new int[] {newSize, x, y, 0};
                    }
                }
                // Remove right wall
                if (x != M-1 && roomID[y][x] != roomID[y][x+1]) {
                    int newSize = roomSizes.get(roomID[y][x]) + roomSizes.get(roomID[y][x+1]);
                    if (newSize > bestWall[0]) {
                        // New best
                        bestWall = new int[] {newSize, x, y, 1};
                    }
                }
            }
        }

        return bestWall;
    }

    int floodfill() {
        int maxRoomSize = -1;
        roomSizes = new ArrayList<Integer>();
        roomSizes.add(-1);
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (roomID[y][x] == 0) {
                    // Explore this room
                    int roomSize = exploreRoom(x, y, numRooms + 1);
                    numRooms++;
                    maxRoomSize = Math.max(roomSize, maxRoomSize);
                    roomSizes.add(roomSize);
                }
            }
        }

        return maxRoomSize;
    }

    int exploreRoom(int x, int y, int id) {
        int roomSize = 0;
        roomID[y][x] = id;

        // Explore in all directions
        int nx, ny;
        for (int i = 0; i < 4; i++) {
            if ((walls[y][x] & hasWall[i]) != 0) continue;
            nx = x + cx[i];
            ny = y + cy[i];
            if (roomID[ny][nx] == 0) {
                roomSize += exploreRoom(nx, ny, id);
            }
        }

        return roomSize + 1;
    }

    public static void main(String[] args) throws IOException {
        new castle();
    }
}