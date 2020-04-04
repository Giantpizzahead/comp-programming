import java.util.*;

public class D {
    int N;
    int[] maxVal;

    D() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        maxVal = new int[51];
        for (int i = 0; i < N; i++) {
            int s = sc.nextInt();
            int v = sc.nextInt();
            maxVal[s] = Math.max(v, maxVal[s]);
        }
        int answer = 0;
        for (int i = 1; i < 51; i++) answer += maxVal[i];
        System.out.println(answer);
    }

    public static void main(String[] args) {
        new D();
    }
}
