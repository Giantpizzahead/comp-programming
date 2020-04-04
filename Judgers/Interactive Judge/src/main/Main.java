package main;

import contest.tasks.*;
import gui.*;
import java.io.*;
import java.util.*;
import java.nio.file.*;

public class Main {
    public final static boolean DEBUG = true;

    public static Task[] tasks;
    public static int numTasks;

    public static void main(String[] args) throws IOException {
        parseAllTasks();
        GUI gui = new GUI();
    }

    public static void parseAllTasks() {
        // Make panes for every found task
        ArrayList<Task> taskList = new ArrayList<>();
        try {
            for (Path paths : Files.newDirectoryStream(Paths.get("tasks"))) {
                if (DEBUG) System.out.println("Parsing task: " + paths.toString());
                taskList.add(new JSONTask(paths.toString()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        tasks = taskList.toArray(new Task[0]);
        numTasks = tasks.length;
    }
}
