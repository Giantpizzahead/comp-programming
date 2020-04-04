/*
Solution: 

Runtime: 
*/

import java.util.*;
import java.io.*;

public class magnumopus {
    int[] arr;
    int[] amounts = {1, 1, 2, 7, 4};

    magnumopus(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        arr = new int[5];
        for (int i = 0; i < 5; i++) arr[i] = Integer.parseInt(st.nextToken());
        int answer = 9999;
        for (int i = 0; i < 5; i++) answer = Math.min(arr[i] / amounts[i], answer);
        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new magnumopus(in, out);
        in.close();
        out.close();
    }
}
