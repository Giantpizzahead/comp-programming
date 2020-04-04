package contest.tasks;

import com.google.gson.Gson;
import contest.Submission;

import java.io.FileReader;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

/**
 * A class that uses a JSON file to initialize the task (IOI 2019).
 * @author Giantpizzahead
 */
public class JSONTask extends Task {
    private static final Gson gson = new Gson();

    public JSONTask(String taskFolder) {
        this.taskFolder = taskFolder;
        this.grader = "/graders/grader.java";
        this.checker = "/checkers/checker.exe";
        try {
            parseProblemJSON();
            parseSubtasksJSON();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void parseProblemJSON() throws IOException {
        info = gson.fromJson(new FileReader(taskFolder + "/problem.json"), ProblemInfo.class);
    }

    private void parseSubtasksJSON() throws IOException {
        Path dir = Paths.get(taskFolder + "/subtasks");
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(dir)) {
            ArrayList<Subtask> subtasks = new ArrayList<>();
            for (Path entry : stream) {
                subtasks.add(gson.fromJson(new FileReader(entry.toFile()), Subtask.class));
            }
            this.subtasks = subtasks.toArray(new Subtask[0]);
        }
    }

    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append(gson.toJson(info));
        result.append('\n');
        for (Subtask s : subtasks) {
            result.append(gson.toJson(s));
            result.append('\n');
        }
        return result.toString();
    }
}
