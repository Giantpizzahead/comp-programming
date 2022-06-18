import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class G {
 
    static class Node implements Comparable<Node>{
        int start;
        long point;
        int time;
        Node(long point, int time, int start){
            this.point = point;
            this.time = time;
            this.start = start;
        }
        public int compareTo(Node s){
            if(start == s.start){
                if(point > s.point) return 1;
                else if(point < s.point) return - 1;
                return 0;
            }
            return start - s.start;
        }
    }
 
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken()), t = Integer.parseInt(st.nextToken());
        //0 - i, 1 - point, 2 - time, 3 - deadline
        Node[] ar = new Node[n];
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            Integer.parseInt(st.nextToken());
            ar[i] = new Node(Long.parseLong(st.nextToken()), Integer.parseInt(st.nextToken()), 0);
            ar[i].start = Integer.parseInt(st.nextToken()) - ar[i].time;
        }
        long[] dp = new long[t + 1];
        for (int i = 1; i <= t; i++) {
            dp[i] = -1;
        }
        Arrays.sort(ar);
        long ans = 0L;
        for (int i = 0; i < n; i++) {
            for (int j = Math.min(ar[i].start, t - ar[i].time); j >= 0; j--) {
                if(dp[j] == -1) continue;
                dp[j + ar[i].time] = Math.max(dp[j + ar[i].time], dp[j] + ar[i].point);
                ans = Math.max(ans, dp[j + ar[i].time]);
            }
        }
        System.out.println(ans);
    }
}