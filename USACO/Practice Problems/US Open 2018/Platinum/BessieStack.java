import java.io.IOException;

public class BessieStack extends Grader {
    final int STACK_SIZE = 5496;

    public static void main(String[] args) throws IOException { new BessieStack().run(); }

    /*
    public static void main(String[] args) {
        new Bessie();
    }

    Bessie() {
        notebook = new int[5500];
        stackAdd(1, 2);
        stackAdd(3, 4);
        stackAdd(5, 6);
        stackAdd(8, 9);
        stackPop();
        stackPopBack();
        stackAdd(9, 10);
        stackAdd(11, 12);
        System.out.println(Arrays.toString(Arrays.copyOfRange(notebook, 0, 20)));
        System.out.println("Stack front: " + getStackFront());
        System.out.println("Stack back: " + getStackBack());
        System.out.println("Stack size: " + getStackSize());
    }
     */

    @Override
    public void helpBessie(int ID) {
        int N = getTrainLength();
        int K = getWindowLength();
        int carI = getCurrentCarIndex();
        int pass = getCurrentPassIndex();
        if (pass == 1) return;

        // Store elements in form (index, value)
        int size = getStackSize();
        // Remove all previous values with higher value than this one
        while (size != 0 && stackPeekFront().b > ID) {
            stackPop();
            size--;
        }
        // Remove first value if its index is out of the window
        if (size != 0 && stackPeekBack().a <= carI - K) {
            stackPopBack();
        }

        // Add this value
        stackAdd(carI, ID);

        // Output current window min (if needed)
        if (carI >= K - 1) shoutMinimum(stackPeekBack().b);
    }

    private void stackAdd(int index, int ID) {
        if (getStackSize() >= STACK_SIZE / 2) {
            // Can no longer add elements; just hope that this doesn't get used
        } else {
            // Add element to stack
            int front = getStackFront();
            setStackSize(getStackSize() + 1);
            set(front, index);
            set(front+1, ID);
            front += 2;
            if (front >= STACK_SIZE) {
                front -= STACK_SIZE;
            }
            setStackFront(front);
        }
    }

    private void stackPop() {
        int front = getStackFront() - 2;
        setStackSize(getStackSize() - 1);
        if (front < 0) {
            front += STACK_SIZE;
        }
        setStackFront(front);
    }

    private void stackPopBack() {
        int back = getStackBack();
        back += 2;
        setStackSize(getStackSize() - 1);
        if (back >= STACK_SIZE) back -= STACK_SIZE;
        setStackBack(back);
    }

    private Pair stackPeekFront() {
        int iToGet = getStackFront() - 2;
        if (iToGet < 0) iToGet += STACK_SIZE;
        return new Pair(get(iToGet), get(iToGet+1));
    }

    private Pair stackPeekBack() {
        int iToGet = getStackBack();
        return new Pair(get(iToGet), get(iToGet+1));
    }

    private int getStackSize() {
        return get(5497);
    }

    private void setStackSize(int size) {
        set(5497, size);
    }

    private int getStackFront() {
        return get(5499);
    }

    private void setStackFront(int index) {
        set(5499, index);
    }

    private int getStackBack() {
        return get(5498);
    }

    private void setStackBack(int index) {
        set(5498, index);
    }

    static class Pair {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}