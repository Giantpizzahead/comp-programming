package contest.tasks;

import com.google.gson.*;
import contest.Submission;

import java.io.*;
import java.nio.file.*;
import java.util.*;

/**
 * A class representing one IOI task. Contains all the info required for the task, like its
 * name, the subtasks, and the type of task (batch or output-only).
 * @author Giantpizzahead
 */
public class Task {
    public static class ProblemInfo {
        private String code, name, task_type;
        private int memory_limit, score_precision;
        private double time_limit;
    }

    public static class Subtask {
        private int score;
        private String[] testcases;

        public int getMaxScore() {
            return score;
        }

        public String[] getTestcases() {
            return testcases;
        }
    }

    public String taskFolder, grader, checker;
    protected ProblemInfo info;
    public Subtask[] subtasks;
    public Submission lastSubmission;
    public double bestScore = 0;

    public String getCodename() {
        return info.code;
    }

    public String getFullname() {
        return info.name;
    }

    public String getTaskType() {
        return info.task_type;
    }

    public int getMemoryLimit() {
        return info.memory_limit;
    }

    public double getTimeLimit() {
        return info.time_limit;
    }

    public String toString() {
        return info.name + " (" + info.code + ")";
    }
}
