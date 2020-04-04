import java.util.*;

public class Grader {
    int N, K, i, passIndex;
    int[] cars, notebook;
    ArrayList<Integer> givenAnswers;

    public void run() {
        K = 678;
        System.out.println("K = " + K);
        cars = new int[1000];
        for (int i = 0; i < 1000; i++) cars[i] = (int) (Math.random() * 100) + i;
        N = cars.length;
        notebook = new int[5500];
        passIndex = 0;
        givenAnswers = new ArrayList<>();
        for (i = 0; i < N; i++) {
            helpBessie(cars[i]);
        }

        System.out.println(Arrays.toString(Arrays.copyOfRange(notebook, 4000, 4008)));

        passIndex = 1;
        for (i = 0; i < N; i++) {
            helpBessie(cars[i]);
        }

        System.out.println(Arrays.toString(Arrays.copyOfRange(notebook, 0, 20)));

        System.out.println("Checking answers...");
        for (int i = 0; i < N - K; i++) {
            int min = 1000000007;
            for (int j = i; j < i + K; j++) min = Math.min(cars[j], min);
            if (min != givenAnswers.get(i)) System.out.println("Wrong answer! Min #" + i + ": " + givenAnswers.get(i) + " != " + min);
        }
    }

    public int get(int index) {
        return notebook[index];
    }

    public void set(int index, int value) {
        notebook[index] = value;
    }

    public int getTrainLength() {
        return N;
    }

    public int getWindowLength() {
        return K;
    }

    public int getCurrentCarIndex() {
        return i;
    }

    public int getCurrentPassIndex() {
        return passIndex;
    }

    public void helpBessie(int ID) {
        return;
    }

    public void shoutMinimum(int output) {
        // System.out.println(output);
        givenAnswers.add(output);
    }
}
