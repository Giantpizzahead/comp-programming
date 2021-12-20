package misc;

import main.*;
import java.io.IOException;
import java.io.InputStreamReader;

public class Terminal {
    private static final Runtime runtime = Runtime.getRuntime();
    public static final Process terminal;
    static {
        Process terminal1;
        try {
            terminal1 = runtime.exec("bash");
        } catch (IOException e) {
            e.printStackTrace();
            terminal1 = null;
        }
        terminal = terminal1;
    }

    public static int execute(String cmd) {
        try {
            if (Main.DEBUG) System.out.println("> " + cmd);
            Process process = runtime.exec(cmd);
            int code = process.waitFor();
            if (code != 0 && Main.DEBUG) {
                System.err.println("Error occurred while executing " + cmd + ":\n");
                process.getErrorStream().transferTo(System.err);
            }
            return code;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public static InteractiveProcess executeInteractive(String cmd) {
        try {
            if (Main.DEBUG) System.out.println("> " + cmd);
            return new InteractiveProcess(runtime.exec(cmd));
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}
