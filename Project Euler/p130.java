public class p130 {
    int N = 250;

    public p130() {
        long sum = 0;
        int numFound = 0;
        for (int n = 3; numFound < N; n += 2) {
            if (n % 5 == 0 || isPrime(n)) continue;
            if (test(n)) {
                System.out.println(n + " works");
                sum += n;
                numFound++;
            }
        }
        System.out.println(sum);
    }

    boolean isPrime(int n) {
        for (int i = 2; i < (int) Math.sqrt(n) + 2; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    boolean test(int n) {
        int remainder = 1, length = 2;
        while (length <= n) {
            remainder = remainder * 10 + 1;
            remainder %= n;
            if (remainder == 0) {
                // Is n-1 divisible by A(n)?
                return (n - 1) % length == 0;
            }
            length++;
        }
        return false;
    }

    public static void main(String[] args) {
        new p130();
    }
}
