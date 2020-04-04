package contest.judges;

import contest.*;
import contest.tasks.Task;

import java.io.File;

public class OutputOnlyJudge extends Judge {
    public OutputOnlyJudge(Task task, File submission) {
        super(task, submission);
    }

    @Override
    protected boolean initJudge() {
        return true;
    }

    @Override
    protected TestResult runTest(String testcase, int testNum) {
        return null;
    }
}
