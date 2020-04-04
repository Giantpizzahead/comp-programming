import java.util.*;

public class I {

    I() {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        sc.nextLine();
        char[][] grid = new char[N][N];
        for (int i = 0; i < N; i++) grid[i] = sc.nextLine().toCharArray();
        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(grid[i]));

        boolean[][] visited = new boolean[N][N];
        for (int i = 0; i < N; i++) {
            if (grid[i][0] == 'L') visited[i][0] = true;
        }
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[j][i] == 'L') {
                    boolean canTrans = false;
                    for (int k = Math.max(j-2, 0); k <= Math.min(j+2, N-1); k++) {
                        if (visited[k][i-1]) {
                            canTrans = true;
                            break;
                        }
                    }
                    visited[j][i] = canTrans;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (j != 0) System.out.print(' ');
                System.out.print(visited[i][j] ? 1 : 0);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        new I();
    }
}
