package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import contest.tasks.Task;
import main.*;

public class GUI extends JFrame implements ActionListener {
    private JTabbedPane tabbedPane;
    private JPanel tempPanel;
    public JButton submitButton;
    public boolean alreadySubmitted = false;

    public GUI() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("IOI Judge");
        setMinimumSize(new Dimension(360, 880));
        setSize(new Dimension(720, 880));

        // Initialize the top menu bar
        JMenuBar mb = new JMenuBar();

        JMenu m1 = new JMenu("Contest");
        JMenuItem m11 = new JMenuItem("Start!");
        JMenuItem m12 = new JMenuItem("Reset");
        m11.addActionListener(this);
        m12.addActionListener(this);
        m1.add(m11);
        m1.add(m12);
        mb.add(m1);

        JMenu m2 = new JMenu("Settings");
        JMenuItem m21 = new JMenuItem("Contest Time Limit");
        JMenuItem m22 = new JMenuItem("About");
        m2.add(m21);
        m2.add(m22);
        m21.addActionListener(this);
        m22.addActionListener(this);
        mb.add(m2);

        JMenu m3 = new JMenu("Debug");
        JMenuItem m31 = new JMenuItem("Reset / Reload Tasks");
        m3.add(m31);
        m31.addActionListener(this);
        mb.add(m3);

        add(mb, BorderLayout.NORTH);

        // Initialize the center tabbed pane
        tabbedPane = new JTabbedPane();
        tabbedPane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);

        // Initialize the bottom submit menu
        JPanel panel = new JPanel();
        submitButton = new JButton("Submit!");
        submitButton.addActionListener(this);
        panel.add(submitButton);

        add(panel, BorderLayout.SOUTH);

        // Make temporary waiting screen while parsing tasks
        tempPanel = new JPanel();
        tempPanel.setLayout(new GridBagLayout());
        JLabel tempLabel = new JLabel("Parsing tasks...  ");
        JProgressBar tempProgressBar = new JProgressBar();
        tempProgressBar.setIndeterminate(true);
        tempPanel.add(tempLabel);
        tempPanel.add(tempProgressBar);

        // Make the whole thing visible
        setVisible(true);
        parsingWait();
        setupTabs();
    }

    public void parsingWait() {
        remove(tabbedPane);
        add(tempPanel, BorderLayout.CENTER);
        validate();
    }

    public void setupTabs() {
        tabbedPane.removeAll();

        // Create all panes
        for (int i = 0; i < Main.numTasks; i++) {
            Task task = Main.tasks[i];
            TaskPanel taskPanel = new TaskPanel(this, task, i);
            tabbedPane.addTab(taskPanel.title, taskPanel);
        }

        // Display the tabs
        remove(tempPanel);
        add(tabbedPane, BorderLayout.CENTER);
        validate();
    }

    public void handleSubmission() {
        if (alreadySubmitted) return;
        FileDialog chooser = new FileDialog((Dialog) null, "Select file to submit");
        chooser.setMode(FileDialog.LOAD);
        chooser.setVisible(true);
        if (chooser.getFile() != null) {
            String fileToSubmit = chooser.getDirectory() + chooser.getFile();
            alreadySubmitted = true;
            submitButton.setEnabled(false);
            ((TaskPanel) tabbedPane.getSelectedComponent()).handleSubmission(fileToSubmit);
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        if (source instanceof JMenuItem) {
            JMenuItem mi = (JMenuItem) source;
            switch (mi.getText()) {
                case "Start!":
                    JComponent panel = new JPanel();
                    tabbedPane.addTab("cool " + tabbedPane.getTabCount(), panel);
                    break;
                case "Reset / Reload Tasks":
                    if (alreadySubmitted) return;
                    Main.parseAllTasks();
                    setupTabs();
                    break;
            }
        } else if (source instanceof JButton) {
            JButton button = (JButton) source;
            switch (button.getText()) {
                case "Submit!":
                    handleSubmission();
                    break;
            }
        }
    }
}
