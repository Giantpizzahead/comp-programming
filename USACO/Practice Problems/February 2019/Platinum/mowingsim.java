import java.util.Arrays;

public class mowingsim {
    public static void main(String[] args) {
        int S = 20;
        int[][] result = new int[S][S];
        for (int i = 1; i <= S; i++) {
            for (int j = 1; j <= S; j++) {
                result[i-1][S-j] = i * j + (S + 1 - i) * (S + 1 - j);
            }
        }

        for (int i = 0; i < S; i++) {
            System.out.println(Arrays.toString(result[i]));
        }
    }
}
