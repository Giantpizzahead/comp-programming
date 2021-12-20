package contest;
import contest.judges.*;
import contest.tasks.Task;
import main.Main;

import java.io.*;

/**
 * A class representing one submission to a task. Handles all the grading / gives verbose
 * details as to what is happening.
 * @author Giantpizzahead
 */
public class Submission implements Runnable {
    private Task task;
    private File submission;
    private Judge judge;
    private double currScore;
    private Thread thread;
    public boolean running = false;
    public Judge.JudgeResult judgeResult;

    public Submission(Task task, File submission) {
        this.task = task;
        this.submission = submission;
    }

    public void startGrading() {
        thread = new Thread(this);
        thread.start();
        running = true;
    }

    @Override
    public void run() {
        switch (task.getTaskType()) {
            case "Batch":
                judge = new BatchJudge(task, submission);
                break;
            case "Output-Only":
                judge = new OutputOnlyJudge(task, submission);
                break;
            default:
                System.err.println("Unknown task type: " + task.getTaskType());
                judgeResult = new Judge.JudgeResult(0);
                judgeResult.finalScore = -1;
                judgeResult.firstBadVerdict = "ERROR";
                running = false;
                return;
        }
        judge.run();
        judgeResult = judge.getJudgeResult();
        if (Main.DEBUG) showResults(judge.getJudgeResult());
        running = false;
    }

    void showResults(Judge.JudgeResult judgeResult) {
        System.out.println("Subtask  |  Score  |  Test  |  Time  |  Memory  |  Verdict");
        for (int i = 0; i < judgeResult.numSubtasks; i++) {
            System.out.printf("  %2d     |  %5.2f  |  %3s   | %4dms |  %4dmb  | %5s\n",
                    i,
                    judgeResult.subtaskScores[i],
                    judgeResult.testResults[i].comment.equals("AC") ? "-" : judgeResult.testNums[i],
                    judgeResult.testResults[i].ms,
                    judgeResult.testResults[i].mem,
                    judgeResult.testResults[i].comment);
        }
    }

    public String getInfoMessage() {
        if (judge == null) return "Waiting...";
        else return judge.getInfoMessage();
    }
}
