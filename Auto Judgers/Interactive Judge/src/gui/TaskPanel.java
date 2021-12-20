package gui;

import contest.*;
import contest.judges.Judge;
import contest.tasks.Task;

import java.awt.event.*;
import java.io.*;
import java.text.SimpleDateFormat;
import javax.swing.*;
import javax.swing.Timer;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.util.*;

public class TaskPanel extends JPanel implements ActionListener {
    private GUI gui;
    private Task task;
    private JLabel subStatusLabel, bestScoreLabel;
    private JTable subtasksTable, resultTable;
    private Submission submission;
    private ArrayList<Judge.JudgeResult> pastResults = new ArrayList<>(2);
    private Timer updateTimer = new Timer(100, this);
    public int taskNum;
    public String title;

    public TaskPanel(GUI gui, Task task, int taskNum) {
        this.gui = gui;
        this.task = task;
        this.taskNum = taskNum;
        title = (char) ('A' + taskNum) + ". " + task.getFullname();

        setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        setLayout(new BorderLayout());

        // Create the 3 panels
        JPanel topPanel = new JPanel();
        topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.PAGE_AXIS));
        JPanel midPanel = new JPanel();
        midPanel.setLayout(new BoxLayout(midPanel, BoxLayout.PAGE_AXIS));
        JPanel botPanel = new JPanel();
        botPanel.setLayout(new BoxLayout(botPanel, BoxLayout.PAGE_AXIS));

        // Task title
        JLabel tlabel = new JLabel(task.getFullname());
        tlabel.setFont(new Font("Dialog", Font.BOLD, 30));
        tlabel.setHorizontalAlignment(JLabel.CENTER);
        topPanel.add(tlabel);

        Font dialogFont = new Font("Dialog", Font.PLAIN, 18);

        // Code name
        JLabel clabel = new JLabel("Code name: " + task.getCodename());
        clabel.setFont(dialogFont);
        topPanel.add(clabel);

        // Task type
        JLabel typelabel = new JLabel("Task type: " + task.getTaskType());
        typelabel.setFont(dialogFont);
        topPanel.add(typelabel);

        // Time limit
        JLabel llabel = new JLabel();
        llabel.setFont(dialogFont);
        if (task.getTimeLimit() % 1 == 0) {
            llabel.setText("Time limit: " + Math.round(task.getTimeLimit()) + " second" + ((task.getTimeLimit() == 1) ? "" : "s"));
        } else {
            llabel.setText("Time limit: " + task.getTimeLimit() + " seconds");
        }
        topPanel.add(llabel);

        // Memory limit
        JLabel memlabel = new JLabel("Memory limit: " + task.getMemoryLimit() + " MB");
        memlabel.setFont(dialogFont);
        topPanel.add(memlabel);

        midPanel.setBorder(BorderFactory.createEmptyBorder(25, 0, 25, 0));
        
        // Best score so far
        bestScoreLabel = new JLabel("Best score: 0");
        bestScoreLabel.setFont(dialogFont);
        midPanel.add(bestScoreLabel);

        // Submission status
        subStatusLabel = new JLabel("Not submitted yet");
        subStatusLabel.setFont(dialogFont);
        midPanel.add(subStatusLabel);

        // Last submission detailed results
        subtasksTable = new JTable(new SubtasksTableModel(new Object[task.subtasks.length][6], new String[]{"Subtask", "Score", "Test", "Time", "Memory", "Verdict"}));
        subtasksTable.setFillsViewportHeight(false);
        subtasksTable.setPreferredScrollableViewportSize(new Dimension(subtasksTable.getPreferredScrollableViewportSize().width, Math.min(task.subtasks.length * 35, 210)));
        subtasksTable.setCellSelectionEnabled(false);
        subtasksTable.getTableHeader().setReorderingAllowed(false);
        subtasksTable.getTableHeader().setFont(dialogFont);
        subtasksTable.setFont(new Font("Dialog", Font.PLAIN, 16));
        subtasksTable.setRowHeight(35);
        for (int i = 0; i < task.subtasks.length; i++) {
            if (task.getTaskType().equals("OutputOnly")) subtasksTable.setValueAt(i+1, i, 0);
            else if (i == 0) subtasksTable.setValueAt('S', i, 0);
            else subtasksTable.setValueAt(i, i, 0);
        }
        JScrollPane scrollPane1 = new JScrollPane(subtasksTable);
        scrollPane1.setBorder(BorderFactory.createEmptyBorder(0, 0, 10, 0));
        botPanel.add(scrollPane1, BorderLayout.NORTH);

        // Past submission results table (scrollable!)
        resultTable = new JTable(new ResultsTableModel(new String[] {"Time", "Score", "Verdict"}));
        resultTable.setFillsViewportHeight(false);
        resultTable.setPreferredScrollableViewportSize(new Dimension(resultTable.getPreferredScrollableViewportSize().width, 210));
        resultTable.setCellSelectionEnabled(false);
        resultTable.getTableHeader().setReorderingAllowed(false);
        resultTable.getTableHeader().setFont(dialogFont);
        resultTable.setFont(new Font("Dialog", Font.PLAIN, 16));
        resultTable.setRowHeight(35);
        JScrollPane scrollPane2 = new JScrollPane(resultTable);
        scrollPane2.setBorder(BorderFactory.createEmptyBorder(10, 0, 0, 0));
        botPanel.add(scrollPane2, BorderLayout.SOUTH);

        add(topPanel, BorderLayout.NORTH);
        add(midPanel, BorderLayout.CENTER);
        add(botPanel, BorderLayout.SOUTH);

        updateTimer.start();
    }

    public void handleSubmission(String fileToSubmit) {
        submission = new Submission(task, new File(fileToSubmit));
        submission.startGrading();
    }

    private void displaySubmissionResults() {
        Judge.JudgeResult jr = submission.judgeResult;
        
        // Update subtask table
        for (int i = 0; i < jr.subtaskScores.length; i++) {
            subtasksTable.setValueAt(formatScore(jr.subtaskScores[i]), i, 1);
            subtasksTable.setValueAt(jr.testResults[i].comment.equals("AC") ? "-" : jr.testNums[i], i, 2);
            subtasksTable.setValueAt(jr.testResults[i].ms + "ms", i, 3);
            subtasksTable.setValueAt(jr.testResults[i].mem + "mb", i, 4);
            subtasksTable.setValueAt(jr.testResults[i].comment, i, 5);
        }

        // Update results table
        ResultsTableModel model = (ResultsTableModel) resultTable.getModel();
        Object[] newRow = new Object[3];
        newRow[0] = new SimpleDateFormat("HH:mm:ss").format(new Date());
        newRow[1] = formatScore(jr.finalScore);
        newRow[2] = jr.firstBadVerdict;
        model.addRow(newRow);

        // Update best score (if needed)
        if (task.bestScore < jr.finalScore) {
            task.bestScore = jr.finalScore;
            bestScoreLabel.setText("Best score: " + formatScore(task.bestScore));
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        if (source instanceof Timer) {
            // Update submission status message / check for completion
            if (submission == null) {
                if (pastResults.size() > 0) subStatusLabel.setText("Last score: " + formatScore(pastResults.get(pastResults.size() - 1).finalScore));
                else subStatusLabel.setText("Not submitted yet");
            } else {
                subStatusLabel.setText(submission.getInfoMessage());
                if (!submission.running) {
                    // Display results of submission
                    displaySubmissionResults();
                    pastResults.add(submission.judgeResult);
                    gui.alreadySubmitted = false;
                    gui.submitButton.setEnabled(true);
                    submission = null;
                }
            }
        }
    }

    private String formatScore(double score) {
        if (score % 1 == 0) return Long.toString(Math.round(score));
        else return String.format("%.2f", score);
    }

    static class SubtasksTableModel extends AbstractTableModel {
        private String[] columnNames;
        private Object[][] data;

        private SubtasksTableModel(Object[][] data, String[] columnNames) {
            this.columnNames = columnNames;
            this.data = data;
        }

        @Override
        public int getRowCount() {
            return data.length;
        }

        @Override
        public int getColumnCount() {
            return columnNames.length;
        }

        @Override
        public String getColumnName(int col) {
            return columnNames[col];
        }

        @Override
        public Object getValueAt(int row, int col) {
            return data[row][col];
        }

        @Override
        public void setValueAt(Object value, int row, int col) {
            data[row][col] = value;
            fireTableCellUpdated(row, col);
        }
    }

    static class ResultsTableModel extends AbstractTableModel {
        private String[] columnNames;
        private ArrayList<Object[]> data = new ArrayList<>();

        private ResultsTableModel(String[] columnNames) {
            this.columnNames = columnNames;
        }

        @Override
        public int getRowCount() {
            return data.size();
        }

        @Override
        public int getColumnCount() {
            return columnNames.length;
        }

        @Override
        public String getColumnName(int col) {
            return columnNames[col];
        }

        @Override
        public Object getValueAt(int row, int col) {
            return data.get(row)[col];
        }

        @Override
        public void setValueAt(Object value, int row, int col) {
            data.get(row)[col] = value;
            fireTableCellUpdated(row, col);
        }

        public void addRow(Object[] newRow) {
            data.add(newRow);
            fireTableRowsInserted(data.size() - 1, data.size() - 1);
        }
    }
}
