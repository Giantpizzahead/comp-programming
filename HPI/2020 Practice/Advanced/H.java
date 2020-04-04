import java.util.*;

public class H {
    int N, M, K, R;
    Store[] stores;
    int[] criminals;

    H() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        K = sc.nextInt();
        R = sc.nextInt();
        stores = new Store[N];
        criminals = new int[K];
        int a, b, p, x;
        for (int i = 0; i < N; i++) {
            a = sc.nextInt();
            b = sc.nextInt();
            p = sc.nextInt();
            stores[i] = new Store(p, b, a);
        }
        for (int i = 0; i < K; i++) {
            x = sc.nextInt();
            criminals[i] = x;
        }
        Arrays.sort(stores, new Comparator<Store>() {
            @Override
            public int compare(Store o1, Store o2) {
                return o1.x - o2.x;
            }
        });
        Arrays.sort(criminals);

        // Get actual store costs
        int criminalI = K-1, addedCrimCost = 0;
        for (int storeI = N-1; storeI >= 0; storeI--) {
            Store s = stores[storeI];
            while (criminalI != -1 && criminals[criminalI] > s.x) {
                addedCrimCost += R;
                criminalI--;
            }
            s.cost += addedCrimCost;
        }

        Arrays.sort(stores, new Comparator<Store>() {
            @Override
            public int compare(Store o1, Store o2) {
                return o1.cost - o2.cost;
            }
        });

        // Greedily purchase from lower cost stores
        int answer = 0, badgesLeft = M;
        for (Store s : stores) {
            while (s.amount > 0 && badgesLeft > 0) {
                s.amount--;
                badgesLeft--;
                answer += s.cost;
            }
            if (badgesLeft == 0) break;
        }
        System.out.println(answer);
    }

    class Store {
        int x, amount, cost;
        Store(int xx, int a, int c) {
            x = xx;
            amount = a;
            cost = c;
        }
    }

    public static void main(String[] args) {
        new H();
    }
}
