package KruskalMaze;

import javax.swing.*;
import java.awt.Font;
import java.util.*;

public class KruskalMaze extends JFrame {
    public JTextField heightTextbox;
    public JCheckBox jCheckBox;
    public JPanel mazePanel;
    public JTextField widthTextbox;

    public static final int North = 1;
    public static final int South = 2;
    public static final int East = 4;
    public static final int West = 8;

    protected Random random = null;
    private int w;
    private int h;
    protected int[][] grid = null;

    public static int directionX(int direction) {
        return switch (direction) {
            case East -> +1;
            case North, South -> 0;
            default -> -1;
        };
    }

    public static int directionY(int direction) {
        return switch (direction) {
            case East, West -> 0;
            case South -> 1;
            default -> -1;
        };
    }

    public static int oppositeOf(int direction) {
        return switch (direction) {
            case East -> West;
            case West -> East;
            case North -> South;
            case South -> North;
            default -> -1;
        };
    }

    public void generateMaze(int s, int width, int height) {
        mazePanel.getGraphics().clearRect(0, 0, getWidth(), getHeight());
        int seed;
        if (s >= 0)
            seed = s;
        else {
            seed = new Random().nextInt(1000);
        }

        random = new Random(seed);

        w = Math.min(width, (mazePanel.getWidth() - 20) / 10);
        h = Math.min(height, (mazePanel.getHeight() - 20) / 10);

//        System.out.println("width " + w + "    " + "height " + h);

        grid = new int[h][w];
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                grid[j][i] = 0;
            }
        }

        List<List<Tree>> sets = new ArrayList<>();
        for (int y = 0; y < h; ++y) {
            List<Tree> tmp = new ArrayList<>();
            for (int x = 0; x < w; ++x) {
                tmp.add(new Tree());
            }
            sets.add(tmp);
        }

        Stack<Edge> edges = new Stack<>();
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (y > 0) {
                    edges.add(new Edge(x, y, North));
                }
                if (x > 0) {
                    edges.add(new Edge(x, y, West));
                }
            }
        }

        for (int i = 0; i < edges.size(); ++i) {
            int pos = random.nextInt(edges.size());
            Edge tmp1 = edges.get(i);
            Edge tmp2 = edges.get(pos);
            edges.set(i, tmp2);
            edges.set(pos, tmp1);
        }

        // Kruskal
        while (edges.size() > 0) {
            Edge tmp = edges.pop();
            int x = tmp.getX();
            int y = tmp.getY();
            int direction = tmp.getDirection();
            int dx = x + directionX(direction), dy = y + directionY(direction);

            Tree set1 = (sets.get(y)).get(x);
            Tree set2 = (sets.get(dy)).get(dx);

            if (!set1.connected(set2)) {
                set1.connect(set2);
                grid[y][x] |= direction;
                grid[dy][dx] |= oppositeOf(direction);
            }
        }

        drawGraphics();
//        Test grid matrix
//        for (int[] ints : grid) {
//            for (int j = 0; j < grid[0].length; j++) {
//                System.out.print(ints[j] + " ");
//            }
//            System.out.println();
//        }
    }

    public KruskalMaze() {
        initComponents();
    }

    private void initComponents() {
        mazePanel = new JPanel();
        JButton jButton = new JButton();
        jCheckBox = new JCheckBox();
        widthTextbox = new JTextField();
        heightTextbox = new JTextField();
        JLabel jLabel = new JLabel();
        JLabel jLabel2 = new JLabel();

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Kruskal Maze");

        mazePanel.setBorder(BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

        GroupLayout mazePanelLayout = new GroupLayout(mazePanel);
        mazePanel.setLayout(mazePanelLayout);
        // Window resolution
        mazePanelLayout.setHorizontalGroup(
                mazePanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGap(0, 600, Short.MAX_VALUE)
        );
        mazePanelLayout.setVerticalGroup(
                mazePanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGap(0, 500, Short.MAX_VALUE)
        );

        jButton.setText("Generate Maze");
        jButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jButtonMouseClicked();
            }
        });

        jCheckBox.setText("Custom width/height");
        jCheckBox.addActionListener(this::jCheckBoxActionPerformed);

        widthTextbox.setEnabled(false);
        heightTextbox.setEnabled(false);
        jLabel.setText("Width:");
        jLabel2.setText("Height:");

        GroupLayout layout = new GroupLayout(getContentPane());

        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                        .addComponent(mazePanel, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addGroup(layout.createSequentialGroup()
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                        .addGroup(layout.createSequentialGroup()
                                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                                                        .addComponent(jCheckBox)
                                                                        .addGroup(layout.createSequentialGroup()
                                                                                .addComponent(jLabel)
                                                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                                                .addComponent(widthTextbox, GroupLayout.PREFERRED_SIZE, 83, GroupLayout.PREFERRED_SIZE)
                                                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                                                .addComponent(jLabel2)))
                                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                                .addComponent(heightTextbox, GroupLayout.PREFERRED_SIZE, 83, GroupLayout.PREFERRED_SIZE)))
                                                .addGap(0, 0, Short.MAX_VALUE))
                                        .addGroup(layout.createSequentialGroup()
                                                .addComponent(jButton)
                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                                .addGap(18, 18, 18)))
                                .addContainerGap())
        );

        layout.setVerticalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                        .addGroup(layout.createSequentialGroup()
                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jButton))))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                        .addGroup(layout.createSequentialGroup()
                                                .addGap(27, 27, 27)
                                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                                        .addComponent(widthTextbox, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(heightTextbox, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                                        .addComponent(jLabel)
                                                        .addComponent(jLabel2)))
                                        .addGroup(layout.createSequentialGroup()
                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(jCheckBox)))
                                .addGap(18, 18, 18)
                                .addComponent(mazePanel, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addGap(5, 5, 5)
                                .addContainerGap())
        );
        pack();
    }

    private void jButtonMouseClicked() {
        if (jCheckBox.isSelected())
            generateMaze(-1, Integer.parseInt(widthTextbox.getText()), Integer.parseInt(heightTextbox.getText()));
        else
            generateMaze(-1, mazePanel.getWidth(), mazePanel.getHeight());
        widthTextbox.setText(String.valueOf(w));
        heightTextbox.setText(String.valueOf(h));
    }

    private void jCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {
        widthTextbox.setEnabled(jCheckBox.isSelected());
        heightTextbox.setEnabled(jCheckBox.isSelected());
    }

    private void drawGraphics() {
        mazePanel.getGraphics().setFont(new Font("Arial", Font.PLAIN, 1));
        int startX = 10;
        int startY = 10;
        int curX;
        int curY;
        for (int i = 0; i < w; i++) {
            curX = (startX + (i * 10)) + 10;
            mazePanel.getGraphics().drawLine(startX + (i * 10), startY, curX, 10);
        }

        curY = startY;
        for (int y = 0; y < h; ++y) {
            curX = startX;
            curY += 10;
            mazePanel.getGraphics().clearRect(curX, curY - 9, 10 * grid[0].length, 10);
            if (y != 0) {
                mazePanel.getGraphics().drawLine(curX, curY - 10, curX, curY);
            }
            for (int x = 0; x < grid[0].length; ++x) {
                if ((grid[y][x] & South) == 0) {
                    mazePanel.getGraphics().drawLine(curX, curY, curX + 10, curY);
                }
                curX += 10;
                if ((grid[y][x] & East) != 0) {
                    if (((grid[y][x] | grid[y][x + 1]) & South) == 0) {
                        mazePanel.getGraphics().drawLine(curX, curY, curX + 10, curY);
                    }
                } else {
                    if (y == h - 1 && x == grid[y].length - 1) {
                        break;
                    } else {
                        mazePanel.getGraphics().drawLine(curX, curY - 10, curX, curY);
                    }
                }
            }
        }
    }
}
