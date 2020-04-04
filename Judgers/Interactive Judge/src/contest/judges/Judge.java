package contest.judges;

import contest.*;
import contest.tasks.Task;
import main.*;
import java.io.*;

public abstract class Judge {
    private static final double INF = 987654321;
    private static final boolean END_ON_FAIL = true;

    protected JudgeResult judgeResult;
    protected File submission;
    protected Task task;
    protected String taskFolder, outPath, infoMessage, cmd;

    public Judge(Task task, File submission) {
        this.submission = submission;
        this.task = task;
        this.taskFolder = "tasks/" + task.getCodename();
        outPath = "out/submissions/" + task.getCodename();
        infoMessage = "Waiting...";
    }

    public void run() {
        if (!initJudge()) {
            // Compile error
            judgeResult = new JudgeResult(task.subtasks.length);
            judgeResult.finalScore = 0;
            judgeResult.firstBadVerdict = "CE";
            for (int i = 0; i < task.subtasks.length; i++) {
                judgeResult.subtaskScores[i] = 0;
                judgeResult.testNums[i] = 1;
                judgeResult.testResults[i] = new TestResult(0, 0, 0, "CE");
            }
            return;
        }

        // Handle each subtask separately
        int testNum = 1;
        judgeResult = new JudgeResult(task.subtasks.length);
        for (int i = 0; i < task.subtasks.length; i++) {
            Task.Subtask subtask = task.subtasks[i];
            double minTCScore = INF;
            int minTCNum = -1, maxMS = 0, maxMem = 0;
            TestResult minTestResult = new TestResult(-1, 0, 0, "-1");
            for (int j = 0; j < subtask.getTestcases().length; j++) {
                String testcase = subtask.getTestcases()[j];
                TestResult result = runTest(testcase, testNum++);
                if (Main.DEBUG) System.out.println("Test " + testNum + ": " + result);
                if (result.score < minTCScore) {
                    minTCScore = result.score;
                    minTestResult = result;
                    minTCNum = j+1;
                }
                maxMS = Math.max(result.ms, maxMS);
                maxMem = Math.max(result.mem, maxMem);
                if (END_ON_FAIL && !result.comment.equals("AC")) break;  // Stop early to save time
            }
            double subtaskScore = subtask.getMaxScore() * minTCScore;
            if (Main.DEBUG) System.out.println("Subtask " + i + ": " + subtaskScore);

            // Update results
            judgeResult.finalScore += subtaskScore;
            if (judgeResult.firstBadVerdict.equals("AC")) judgeResult.firstBadVerdict = minTestResult.comment;
            judgeResult.subtaskScores[i] = subtaskScore;
            judgeResult.testNums[i] = minTCNum;
            judgeResult.testResults[i] = new TestResult(minTestResult.score, maxMS, maxMem, minTestResult.comment);
        }

        // Adjust final score to 2 decimal places
        judgeResult.finalScore = (double) Math.round(judgeResult.finalScore * 100) / 100;
        if (Main.DEBUG) System.out.println("Final score: " + judgeResult.finalScore);
        infoMessage = "Done";
    }

    protected abstract boolean initJudge();

    protected abstract TestResult runTest(String testcase, int testNum);

    public JudgeResult getJudgeResult() {
        return judgeResult;
    }

    public String getInfoMessage() {
        return infoMessage;
    }

    protected String removeExtension(String name) {
        int dotLoc = name.indexOf('.');
        return name.substring(0, dotLoc);
    }

    public static class JudgeResult {
        public int numSubtasks;
        public String firstBadVerdict;
        public double finalScore;
        public double[] subtaskScores;
        public int[] testNums;
        public TestResult[] testResults;

        public JudgeResult(int numSubtasks) {
            this.numSubtasks = numSubtasks;
            firstBadVerdict = "AC";
            subtaskScores = new double[numSubtasks];
            testNums = new int[numSubtasks];
            testResults = new TestResult[numSubtasks];
        }
    }
}
