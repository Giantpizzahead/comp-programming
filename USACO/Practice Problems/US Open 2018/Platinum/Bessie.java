import java.io.IOException;

public class Bessie extends Grader {
    public static void main(String args[]) throws IOException { new Bessie().run(); }

    // Start points are inclusive, end points are exclusive
    // Points on the deque are stored as (index, value) pairs
    final int DEQUE_START = 0, DEQUE_END = 3494, MAX_DEQUE_SIZE = 1747;
    final int PRECOMP_MINS_START = 3495, PRECOMP_MINS_END = 5495;
    final int GET_DEQUE_SIZE = 5496, GET_DEQUE_FRONT = 5497, GET_DEQUE_BACK = 5498;
    final int GET_CURR_WINDOW_END = 5499;
    final int INF = 1000000007, NUM_PER = 500;
    final boolean DEBUG = false;

    @Override
    public void helpBessie(int ID) {
        int carI = getCurrentCarIndex();
        int pass = getCurrentPassIndex();
        if (pass == 0) {
            // First pass: Precompute minimums for every 1000 elements
            if (carI == 0) {
                // Initial setup (make everything INF)
                for (int i = PRECOMP_MINS_START; i < PRECOMP_MINS_END; i++) {
                    set(i, INF);
                }
            }

            int precompIndex = PRECOMP_MINS_START + carI / NUM_PER;
            set(precompIndex, Math.min(get(precompIndex), ID));
        } else {
            // Second pass: Keep track of minimums in a stack, and output answers as needed
            if (carI == 0) {
                // Initial setup
                // windowEnd always contains the point at which Bessie needs to shout a new answer
                setWindowEnd(getWindowLength() - 1);
            }
            if (currWindowEnd() >= getTrainLength()) return;  // Done already

            // Remove elements from front of deque until the front element has a lower value than the current one
            while (dequeSize() != 0 && dequePeekFront().value >= ID) {
                dequePollFront();
            }

            // Add the current element
            dequeAdd(new Point(carI, ID));

            // If deque is getting big, try to lower its size
            if (dequeSize() > NUM_PER && carI % NUM_PER == NUM_PER - 1) {
                optimizeDeque(carI, ID);
            }

            // Remove element from back of deque if out of window range
            if (dequeSize() != 0 && dequePeekBack().index <= currWindowEnd() - getWindowLength()) {
                dequePollBack();
            }

            // If window answer needs to be outputted, output it
            if (currWindowEnd() == carI) {
                shoutMinimum(dequePeekBack().value);
                setWindowEnd(currWindowEnd() + 1);
            }
        }
    }

    void optimizeDeque(int carI, int ID) {
        if (DEBUG) System.out.println("Deque being optimized at size " + dequeSize() + "... (" + carI + ", " + ID + ")");
        int precompIndex = PRECOMP_MINS_START + (carI + 1) / NUM_PER;
        int nextRangeMin = get(precompIndex);
        // System.out.println("nextRangeMin = " + nextRangeMin);

        if (nextRangeMin < ID) {
            // Remove elements from deque front that have higher values than next range minimum until deque size is
            // <= 1000 (those elements will never be used in minimum)
            // Also don't add this element
            if (DEBUG) System.out.println(nextRangeMin + " < " + ID);
            while (dequeSize() > NUM_PER && nextRangeMin < dequePeekFront().value) {
                dequePollFront();
            }
        } else {
            // precompIndex = PRECOMP_MINS_START + (currWindowEnd() + 1) / NUM_PER;
            // nextRangeMin = get(precompIndex);
            while (nextRangeMin >= ID && dequeSize() > 1 && nextRangeMin != INF) {
                // Preoutputting window values up to end of precomputation range is OK (all elements are greater / won't
                // cause an update): Output values up to there.
                // End index is not inclusive
                int precompEndIndex = Math.min(NUM_PER * (precompIndex - PRECOMP_MINS_START + 1), getTrainLength()) - 1;
                if (DEBUG) System.out.println("Precomputing to " + precompEndIndex);
                while (currWindowEnd() < precompEndIndex && dequeSize() > 1) {
                    // Remove element from back of deque if out of window range
                    if (dequeSize() != 0 && dequePeekBack().index <= currWindowEnd() - getWindowLength()) {
                        dequePollBack();
                    }

                    shoutMinimum(dequePeekBack().value);
                    setWindowEnd(currWindowEnd() + 1);
                }
                precompIndex++;
                nextRangeMin = get(precompIndex);
            }
        }
        if (DEBUG) System.out.println("New deque size: " + dequeSize());
    }

    void dequeAdd(Point p) {
        int front = dequeFront();

        if (dequeSize() == MAX_DEQUE_SIZE) {
            if (DEBUG) System.out.println("Adding to a full deque!!!");
            return;
        }

        // Add the point
        set(front, p.index);
        set(front + 1, p.value);

        front += 2;
        if (front >= DEQUE_END) front = DEQUE_START;
        setDequeFront(front);
        setDequeSize(dequeSize() + 1);
    }

    Point dequePollFront() {
        int front = dequeFront();

        if (DEBUG && dequeSize() == 0) System.out.println("Polling front from an empty deque!!!");

        // Get front point
        front -= 2;
        if (front < 0) front = DEQUE_END - 2;
        setDequeFront(front);
        setDequeSize(dequeSize() - 1);

        return new Point(get(front), get(front + 1));
    }

    Point dequePeekFront() {
        int front = dequeFront();

        if (DEBUG && dequeSize() == 0) System.out.println("Peeking front from an empty deque!!!");

        // Get front point
        front -= 2;
        if (front < 0) front = DEQUE_END - 2;
        return new Point(get(front), get(front + 1));
    }

    Point dequePollBack() {
        int back = dequeBack();

        if (DEBUG && dequeSize() == 0) System.out.println("Polling back from an empty deque!!!");

        // Get back point
        Point toReturn = new Point(get(back), get(back + 1));
        back += 2;
        if (back >= DEQUE_END) back = DEQUE_START;
        setDequeBack(back);
        setDequeSize(dequeSize() - 1);

        return toReturn;
    }

    Point dequePeekBack() {
        int back = dequeBack();

        if (DEBUG && dequeSize() == 0) System.out.println("Peeking back from an empty deque!!!");

        // Get back point
        return new Point(get(back), get(back + 1));
    }

    int dequeSize() {
        return get(GET_DEQUE_SIZE);
    }

    void setDequeSize(int v) {
        set(GET_DEQUE_SIZE, v);
    }

    int dequeFront() {
        return get(GET_DEQUE_FRONT);
    }

    void setDequeFront(int v) {
        set(GET_DEQUE_FRONT, v);
    }

    int dequeBack() {
        return get(GET_DEQUE_BACK);
    }

    void setDequeBack(int v) {
        set(GET_DEQUE_BACK, v);
    }

    int currWindowEnd() {
        return get(GET_CURR_WINDOW_END);
    }

    void setWindowEnd(int v) {
        set(GET_CURR_WINDOW_END, v);
    }

    static class Point {
        int index, value;
        Point(int index, int value) {
            this.index = index;
            this.value = value;
        }

        @Override
        public String toString() {
            return "(" + index + ", " + value + ")";
        }
    }
}