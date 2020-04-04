import java.util.*;

public class gymnastsTest {
    static int answer = 0;

    public static void main(String[] args) {
        int minNum = 6;
        int num = 7;
        int[] answers = new int[num];
        for (int i = minNum; i < num; i++) {
            answer = 0;
            System.out.println("Length " + i + ":");
            genConfigs(0, new int[i]);
            answers[i] = answer;
        }
        System.out.println(Arrays.toString(answers));
    }

    static void genConfigs(int i, int[] arr) {
        if (i == arr.length) testConfig(arr);
        else {
            for (int j = 1; j <= arr.length + 20; j++) {
                arr[i] = j;
                genConfigs(i+1, arr);
            }
        }
    }

    static void testConfig(int[] arr) {
        int[] newArr = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            for (int j = i; j < i + arr[i]; j++) {
                int newJ = j % arr.length;
                newArr[newJ]++;
            }
        }

        for (int i = 0; i < arr.length; i++) {
            if (arr[i] != newArr[i]) return;
        }
        // Don't print arrays with all the same
        int first = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] != first) {
                first = -1;
                break;
            }
        }
        answer++;
        if (first != -1) return;
        System.out.println(Arrays.toString(arr));
    }
}
