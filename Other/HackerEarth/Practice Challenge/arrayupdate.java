/*
Solution: Find sum of array elements, and ceiling the division by # of elements.
*/

import java.util.*;
import java.io.*;

public class arrayupdate {
    int N;
    int[] arr;

    arrayupdate() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(in.readLine());
        StringTokenizer st = new StringTokenizer(in.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());
        in.close();

        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += arr[i];
        }
        int x = sum / N + 1;
        System.out.println(x);
    }

    public static void main(String[] args) throws IOException {
        new arrayupdate();
    }
}
