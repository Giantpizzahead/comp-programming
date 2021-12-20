import javax.swing.*;
import java.io.*;
import java.util.*;
import java.nio.file.*;

public class TestRunner {
    // --------------TO EDIT----------------

    long timeLimit = 1000;

    // Useful to avoid typing the same thing over and over again
    String baseFolder = "C:/Users/sunny/OneDrive/Github/ioi-code/Current Problems";

    String testInFolder = "doll/in";
    String inExtension = ".txt";

    boolean hasOutFiles = false;
    String testOutFolder = "doll/out";
    String outExtension = ".txt";

    // If no grader used, set submission to NONE, and put submission as graderFile
    String submission = "src/doll.java";
    String graderFile = "doll/java/grader.java";

    String checkerFolder = "N/A";
    // DIFF to use diff, MANUAL to check output manually, other value to use checker
    String checkerFile = "MANUAL";

    // --------------TO EDIT----------------

    Runtime runtime = Runtime.getRuntime();
    String outFolder = "out/compiled";
    String baseFolderNS, testInFolderNS, testOutFolderNS,
            submissionNS, graderFileNS, checkerFolderNS, outFolderNS;
    String graderFileName, checkerFileName;
    boolean DEBUG = false;

    TestRunner() throws IOException {
        baseFolderNS = translateToLinux(baseFolder);
        testInFolderNS = baseFolderNS + translateToLinux(testInFolder);
        testOutFolderNS = baseFolderNS + translateToLinux(testOutFolder);
        submissionNS = baseFolderNS + translateToLinux(submission);
        graderFileNS = baseFolderNS + translateToLinux(graderFile);
        checkerFolderNS = baseFolderNS + translateToLinux(checkerFolder);
        outFolderNS = translateToLinux(outFolder);
        testInFolder = baseFolder + "/" + testInFolder;
        testOutFolder = baseFolder + "/" + testOutFolder;
        submission = baseFolder + "/" + submission;
        graderFile = baseFolder + "/" + graderFile;
        checkerFolder = baseFolder + "/" + checkerFolder;

        Files.createDirectories(Paths.get(outFolder));
        compileSubmission();
        compileChecker();
        graderFileName = getPlainFileName(graderFile);
        if (!checkerFile.equals("DIFF") && !checkerFile.equals("MANUAL")) checkerFileName = getPlainFileName(checkerFile);
        else checkerFileName = checkerFile;
        for (Path path : Files.newDirectoryStream(Paths.get(testInFolder))) {
            String inputFile = path.toString();
            inputFile = inputFile.replace('\\', '/');
            int dotIndex = inputFile.lastIndexOf('.');
            if (dotIndex == -1) dotIndex = inputFile.length();
            if (!inputFile.substring(dotIndex).equals(inExtension)) continue;
            String testName = getPlainFileName(inputFile);
            inputFile = translateToLinux(inputFile);
            if (hasOutFiles) {
                String answerFile = testOutFolder + "/" + testName + outExtension;
                boolean exists = Files.exists(Paths.get(answerFile));
                if (!exists) System.err.println("Error: " + answerFile + " doesn't exist.");
                answerFile = translateToLinux(answerFile);
                runTest(inputFile, answerFile, testName);
            } else runTest(inputFile, null, testName);
        }
    }

    String translateToLinux(String str) {
        return str.replace(" ", "\\ ").replace("C:", "/mnt/c");
    }

    String getPlainFileName(String filepath) {
        int firstIndex = filepath.lastIndexOf('/');
        int lastIndex = filepath.lastIndexOf('.');
        if (lastIndex == -1) lastIndex = filepath.length();
        return filepath.substring(firstIndex + 1, lastIndex);
    }

    void compileSubmission() {
        if (submission.equals("NONE")) execute("javac -d " + outFolder + " \"" + graderFile + "\"");
        else execute("javac -d " + outFolder + " \"" + graderFile + "\" \"" + submission + "\"");
    }

    void compileChecker() {
        if (!checkerFile.equals("DIFF") && !checkerFile.equals("MANUAL")) {
            execute("bash -c \"make -C " + checkerFolderNS + "\"");
            execute("bash -c \"mv " + checkerFolderNS + "/" + checkerFile + " " + outFolderNS + "\"");
        }
    }

    void runTest(String inputFile, String answerFile, String testName) throws IOException {
        if (DEBUG) System.out.println("Running test " + testName + "...");

        // Run grader using input file
        String outputFile = outFolderNS + "/" + testName + outExtension;
        ProcessRunner procRunner = new ProcessRunner("bash -c \"/usr/jdk/bin/java -Xss256M -cp " + outFolderNS + " " + graderFileName + " < " + inputFile + " > " + outputFile + "\"");
        Thread thread = new Thread(procRunner);
        thread.start();

        // Give the process a bit of pity time (input parsing / other stuff)
        try {
            Thread.sleep(125);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Start timing the process
        long lastTime = System.currentTimeMillis(), currTime;
        int ms = 0;
        while (ms <= timeLimit && (procRunner.process == null || procRunner.process.isAlive())) {
            currTime = System.currentTimeMillis();
            ms += currTime - lastTime;
            lastTime = currTime;
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Did it TLE?
        if (ms > timeLimit) {
            procRunner.process.destroy();
            System.out.println("Test " + testName + ": TLE");
            Files.deleteIfExists(Paths.get(outputFile));
            return;
        }

        // Did it crash?
        if (procRunner.process.exitValue() != 0) {
            System.out.println("Test " + testName + ": RE");
            Files.deleteIfExists(Paths.get(outputFile));
            return;
        }

        // Check output
        if (checkerFile.equals("DIFF")) {
            // Use diff to check correctness
            int code = execute("bash -c \"diff --strip-trailing-cr " + outputFile + " " + answerFile + "\"", false);
            if (code == 0) System.out.println("Test " + testName + ": AC! (" + ms + "ms)");
            else System.out.println("Test " + testName + ": WA (" + ms + "ms)");
        } else if (checkerFile.equals("MANUAL")) {
            // Check output manually
            System.out.print("Test " + testName + " (" + ms + "ms): ");
            BufferedReader fin = new BufferedReader(new FileReader(outputFile));
            fin.lines().forEach(System.out::println);
            fin.close();
        } else {
            // Use checker
            System.out.print("Test " + testName + " (" + ms + "ms): ");
            executeWithOutput("bash -c \"" + outFolderNS + "/" + checkerFile + " " + inputFile + " " + answerFile + " " + outputFile + "\"");
        }
        Files.delete(Paths.get(outputFile));
    }

    class ProcessRunner implements Runnable {
        Process process;
        String cmd;

        ProcessRunner(String cmd) {
            this.cmd = cmd;
        }

        @Override
        public void run() {
            try {
                if (DEBUG) System.out.println("Threaded > " + cmd);
                process = runtime.exec(cmd);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    int execute(String cmd) {
        return execute(cmd, true);
    }

    int execute(String cmd, boolean quitOnError) {
        try {
            if (DEBUG) System.out.println("> " + cmd);
            Process process = runtime.exec(cmd);
            int code = process.waitFor();
            if (code != 0 && quitOnError) {
                System.err.println("Error occurred while executing " + cmd + ":\n");
                process.getErrorStream().transferTo(System.err);
                System.exit(code);
            }
            return code;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        return -1;
    }

    int executeWithOutput(String cmd) {
        return executeWithOutput(cmd, true);
    }

    int executeWithOutput(String cmd, boolean quitOnError) {
        try {
            if (DEBUG) System.out.println("> " + cmd);
            Process process = runtime.exec(cmd);
            int code = process.waitFor();
            if (code != 0 && DEBUG) {
                System.err.println("Error occurred while executing " + cmd + ":\n");
                process.getErrorStream().transferTo(System.err);
                System.exit(code);
            }
            process.getInputStream().transferTo(System.out);
            process.getErrorStream().transferTo(System.err);
            return code;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public static void main(String[] args) throws IOException {
        new TestRunner();
    }
}