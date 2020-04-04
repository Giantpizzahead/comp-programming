package contest.judges;

import contest.*;
import contest.tasks.Task;
import misc.*;
import java.io.*;
import java.nio.file.*;

public class BatchJudge extends Judge {
    private File grader;

    public BatchJudge(Task task, File submission) {
        super(task, submission);
        // Get grader if needed
        grader = new File(task.grader);
    }

    @Override
    protected boolean initJudge() {
        // Create the output directory if needed
        if (!Files.isDirectory(Paths.get(outPath))) {
            try {
                Files.createDirectories(Paths.get(outPath));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // Compile the submission file & grader
        infoMessage = "Compiling submission...";
        cmd = "javac -d " + outPath + " " + grader.getPath() + " \"" + submission.getPath() + "\"";
        if (Terminal.execute(cmd) != 0) return false;

        // Make the checker
        infoMessage = "Compiling checker...";
        cmd = "bash -c \"make -C " + taskFolder + "/checker\"";
        if (Terminal.execute(cmd) != 0) return false;

        // Move the checker to the out submission folder
        cmd = "bash -c \"mv " + taskFolder + "/checker/checker.exe " + outPath + "\"";
        if (Terminal.execute(cmd) != 0) return false;

        return true;
    }

    @Override
    protected TestResult runTest(String testcase, int testNum) {
        infoMessage = "Running test " + testNum + " (" + testcase + ")";
        String inputFile = taskFolder + "/in/" + testcase + ".txt";
        String answerFile = taskFolder + "/out/" + testcase + ".txt";
        String outputFile = outPath + "/" + testcase + ".out";

        try {
            // Execute the grader for this test
            String graderNoExtension = removeExtension(grader.getName());
            cmd = "java -Xss" + task.getMemoryLimit() + "m -Xmx" + task.getMemoryLimit() + "m -cp " + outPath + " " + graderNoExtension;
            InteractiveProcess process = Terminal.executeInteractive(cmd);
            if (process == null) return new TestResult(0, -1, -1, "SV");

            // Send this testcase's data
            BufferedReader fin = new BufferedReader(new FileReader(inputFile));
            String line = fin.readLine();
            while (line != null) {
                process.pout.println(line);
                process.pout.flush();
                line = fin.readLine();
            }
            fin.close();
            process.pout.flush();

            // Time the process
            long maxTime = (long) (task.getTimeLimit() * 1000);
            int maxMem = task.getMemoryLimit();
            long lastTime = System.currentTimeMillis(), currTime;
            int ms = 0, mem = 0;
            long pid = process.process.pid();
            while (ms <= maxTime && mem <= maxMem && process.process.isAlive()) {
                currTime = System.currentTimeMillis();
                ms += currTime - lastTime;
                lastTime = currTime;
                mem = Math.max(16, mem);
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {}
            }

            // Did it TLE?
            if (ms > maxTime) {
                process.process.destroy();
                return new TestResult(0, ms, mem, "TLE");
            }

            // What about MLE (reported as RE)?
            if (mem > maxMem) {
                process.process.destroy();
                return new TestResult(0, ms, mem, "RE");
            }

            // Did it crash?
            if (process.process.exitValue() != 0) {
                return new TestResult(0, ms, mem, "RE");
            }

            // Read output of grader
            process.outputToFile(outputFile);

            // Run the checker on the result to see if it's right
            infoMessage = "Checking test " + testNum + " (" + testcase + ")";
            cmd = "bash -c \"" + outPath + "/checker.exe " + inputFile + " " + answerFile + " " + outputFile + "\"";
            // cmd = "bash -c \"diff --strip-trailing-cr " + answerFile + " " + outputFile + "\"";
            process = Terminal.executeInteractive(cmd);
            if (process == null) return new TestResult(0, ms, mem, "SV");

            // Get checker result
            BufferedReader fout = process.outputToBufferedReader();
            double score = Double.parseDouble(fout.readLine());
            fout.close();

            // Delete previous output file to save space
            // Files.delete(Paths.get(outputFile));

            // Return appropriate feedback
            if (score == 0) return new TestResult(0, ms, mem, "WA");
            else return new TestResult(score, ms, mem, "AC");
        } catch (IOException e) {
            e.printStackTrace();
            return new TestResult(0, -1, -1, "SV");
        }
    }
}
