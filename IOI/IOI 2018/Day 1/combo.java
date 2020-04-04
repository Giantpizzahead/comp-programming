public class combo {
    String guess_sequence(int N) {
        // Find first character
        char firstChar;
        if (combo_lib.press("AB") > 0) {
            if (combo_lib.press("A") == 1) {
                firstChar = 'A';
            } else firstChar = 'B';
        } else {
            if (combo_lib.press("X") == 1) {
                firstChar = 'X';
            } else firstChar = 'Y';
        }

        // Now, use the unique first character to determine all but the last character
        StringBuilder currStr = new StringBuilder(Character.toString(firstChar));
        char[] notFirstChar = new char[3];
        char[] allChars = {'A', 'B', 'X', 'Y'};
        int loc = 0;
        for (char c : allChars) {
            if (c != firstChar) {
                notFirstChar[loc++] = c;
            }
        }

        for (int i = 1; i < N - 1; i++) {
            String str = currStr.toString();
            String queryStr =
                    // If next char is notFirstChar[0], make query return i + 1
                    str +
                    notFirstChar[0] +
                    // If next char is notFirstChar[1], make query return i + 2
                    str +
                    notFirstChar[1] +
                    notFirstChar[0] +
                    str +
                    notFirstChar[1] +
                    notFirstChar[1] +
                    str +
                    notFirstChar[1] +
                    notFirstChar[2];
            // System.out.println(queryStr);
            // If next char is notFirstChar[2], query will return i
            int result = combo_lib.press(queryStr);
            if (result == i) currStr.append(notFirstChar[2]);
            else if (result == i + 1) currStr.append(notFirstChar[0]);
            else currStr.append(notFirstChar[1]);
        }

        // Finally, use the same idea as the 1st character to guess the last character
        if (N != 1) {
            String str = currStr.toString();
            if (combo_lib.press(str + "A" + str + "B") == N) {
                if (combo_lib.press(str + "A") == N) {
                    currStr.append('A');
                } else currStr.append('B');
            } else {
                if (combo_lib.press(str + "X") == N) {
                    currStr.append('X');
                } else currStr.append('Y');
            }
        }

        // System.out.println(currStr);
        return currStr.toString();
    }
}
