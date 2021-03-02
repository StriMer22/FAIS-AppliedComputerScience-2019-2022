package ProbabilityAndStatistics.Task2;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

public class RandPanel extends JPanel {
    int[] nn;
    int n, trials;
    int xmin, xmax;
    double ymax;
    public RandPanel() {
        super();
        xmin = -2;
        xmax = 4;
        ymax = 2.0 / 3;
    }

    public final void generate(int trials, int n) {
        nn = new int[n];
        double d = n / (double)(xmax - xmin);
        for (int i = 0; i < trials; i++) {
            double r = Rand.rand();
            int index = (int)Math.floor((r - xmin) * d);
            nn[index]++;
        }
        this.n = n;
        this.trials = trials;
    }

    @Override
    public void paint(Graphics g) {
        if (nn == null) return;
        int dx = 50;
        int dy = 50;
        Graphics2D g2d = (Graphics2D)g;
        Rectangle r = g2d.getClipBounds();
        if (r == null) return;

        g2d.setBackground(Color.WHITE);
        g2d.clearRect(0, 0, r.width, r.height);

        double xsize = xmax - xmin;
        double ysize = ymax;
        double xscale = (double)(r.width - 50) / xsize;
        double yscale = (double)(r.height - 50) / ysize;
        double step = ((double)r.width - 50) / n;
        int w = (int)step - 1;
        g2d.setColor(Color.BLACK);

        for (int i = xmin; i < xmax; i++) {
            int x = 50 + (int)((i - xmin) * xscale);
            g2d.drawLine(x, r.height - 35, x, 0);
            g2d.drawString(String.valueOf(i), x - 5, r.height - 15);
        }

        for (int i = 0; i < 2; i++) {
            int y = (int)(r.height - 50 - (double)i / 3 * yscale);
            g2d.drawLine(50, y, r.width, y);
            g2d.drawString(i == 0 ? "0" : String.valueOf(i) + "/" + 3, 20, y);
        }

        g2d.setColor(Color.BLUE);
        for (int i = 0; i < n; i++) {
            if (nn[i] == 0) continue;
            int x = (int)(step * i) + 50;
            int y = (int)(((double)nn[i] / trials * n / (xmax - xmin)) * yscale);
            if (w <= 1)
                g2d.drawLine(x, r.height - y - 50, x, r.height - 50);
            else
                g2d.fillRect(x, r.height - y - 50, w, y);
        }

        g2d.setColor(Color.RED);
        g2d.setStroke(new java.awt.BasicStroke(2f));
        g2d.drawLine(dx, r.height - dy, (int)(dx + (-1 - xmin) * xscale), r.height - dy);
        int y = (int)(r.height - dy - 1.0 / 3 * yscale);
        g2d.drawLine((int)(dx + (-1 - xmin) * xscale), r.height - dy, (int)(dx + (-xmin) * xscale), y);
        g2d.drawLine((int)(dx + (-xmin) * xscale), y, (int)(dx + (2 - xmin) * xscale), y);
        g2d.drawLine((int)(dx + (2 - xmin) * xscale), y, (int)(dx + (3 - xmin) * xscale), r.height - dy);
        g2d.drawLine((int)(dx + (3 - xmin) * xscale), r.height - dy, (int)(dx + (4 - xmin) * xscale), r.height - dy);
    }

    public boolean export() {
        if (nn == null) return false;
        Rectangle r = getBounds();
        BufferedImage image = new BufferedImage(r.width, 
                r.height, BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = image.createGraphics();
        g2d.setClip(0, 0, r.width, r.height);
        paint(g2d);
        try {
            FileNameExtensionFilter filter = new FileNameExtensionFilter("PNG files", "png");
            JFileChooser fc = new JFileChooser();
            fc.setFileFilter(filter);
            fc.setCurrentDirectory(new File("."));
            int returnVal = fc.showSaveDialog(this);
            if (returnVal == JFileChooser.APPROVE_OPTION) {
                return ImageIO.write(image, "png", fc.getSelectedFile());
            } else {
                return false;
            }
        } catch (IOException e) {
            return false;
        }
    }

}
