package CodeStar;/*
Solution: Do annoying parsing.
*/

import java.io.*;

public class alphatrees {
    int maxL, maxR;
    boolean inLeft, endLeft, inRight, endRight;

    alphatrees() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line = in.readLine();
        in.close();
        int numParens = 0;
        inLeft = false;
        endLeft = false;
        inRight = false;
        endRight = false;
        maxL = 0;
        maxR = 0;
        StringBuilder num = new StringBuilder();
        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) == '(') {
                numParens++;
                if (numParens == 2 && !endLeft) inLeft = true;
                else if (numParens == 2) inRight = true;
            } else if (line.charAt(i) == ')') {
                numParens--;
                if (numParens == 1 && !endLeft) {
                    inLeft = false;
                    endLeft = true;
                }
                else if (numParens == 1) {
                    inRight = false;
                    endRight = true;
                }
            }

            if (Character.isDigit(line.charAt(i))) {
                // Number
                num.append(line.charAt(i));
            } else if (num.length() != 0) {
                int parsed = Integer.parseInt(num.toString());
                if (inLeft) maxL = Math.max(parsed, maxL);
                else if (inRight) maxR = Math.max(parsed, maxR);
                num = new StringBuilder();
            }
        }

        System.out.println(maxL + maxR);
    }

    public static void main(String[] args) throws IOException {
        new alphatrees();
    }
}
