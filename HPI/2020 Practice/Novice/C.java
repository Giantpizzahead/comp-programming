import java.util.Scanner;

public class C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            if (i != 1) System.out.print(' ');
            int factors = 0;
            for (int j = 1; j <= i; j++) {
                if (i % j == 0) factors++;
            }
            System.out.print(factors);
        }
        System.out.println();
    }
}
