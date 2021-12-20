package Sort;

import java.io.*;
import java.util.StringTokenizer;

public class SortTester {
    int N;
    int[] array;
    PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    SortTester() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(in.readLine());
        array = new int[N];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) array[i] = Integer.parseInt(st.nextToken());

        // Do sorts
        testSorter(new HeapSort());
        testSorter(new QuickSort());
        out.close();
    }

    void testSorter(Sorter sorter) {
        sorter.sort(array);
        for (int i = 0; i < N; i++) {
            out.print(array[i]);
            if (i != N - 1) out.print(' ');
        }
        out.println();
        sorter.printInfo(out);
        out.println();
    }

    public static void main(String[] args) throws IOException {
        new SortTester();
    }
}
