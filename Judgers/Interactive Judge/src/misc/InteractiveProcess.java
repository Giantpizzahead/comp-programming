package misc;

import java.io.*;
import java.util.*;

public class InteractiveProcess {
    public Process process;
    public PrintWriter pout;

    InteractiveProcess(Process process) {
        this.process = process;
        pout = new PrintWriter(process.getOutputStream());
    }

    public void outputToFile(String outFile) {
        try {
            int code = process.waitFor();
            if (code != 0) {
                System.out.println("Error while running test:");
                process.getErrorStream().transferTo(System.err);
            } else {
                BufferedOutputStream fout = new BufferedOutputStream(new FileOutputStream(outFile));
                process.getInputStream().transferTo(fout);
                fout.close();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public BufferedReader outputToBufferedReader() {
        try {
            process.waitFor();
            return new BufferedReader(new InputStreamReader(process.getInputStream()));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }
}
