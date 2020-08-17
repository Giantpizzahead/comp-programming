import java.util.*;
import java.io.*;

public class robotcontest {
    int N, robo, bionic, both;

    robotcontest(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        int[] arr1 = new int[N];
        int[] arr2 = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr1[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr2[i] = Integer.parseInt(st.nextToken());

        both = 0;
        robo = 0;
        bionic = 0;
        for (int i = 0; i < N; i++) {
            if (arr1[i] == 1 && arr2[i] == 1) both++;
            else if (arr1[i] == 1) robo++;
            else if (arr2[i] == 1) bionic++;
        }

        int pointsNeeded = bionic + 1;
        if (robo == 0) out.println(-1);
        else out.println((pointsNeeded + robo - 1) / robo);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new robotcontest(in, out);
        in.close();
        out.close();
    }
}
