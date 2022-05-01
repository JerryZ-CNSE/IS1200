import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Main {

    public static final int pixelsH = 8;
    public static final int pixelsV = 8;
    public static int pixelSize = 40;

    private int mouseX = pixelSize * pixelsV / 2;
    private int mouseY = pixelSize * pixelsH / 2;

    private Screen screen;

    public Main() {
        // Main window
        JFrame frame = new JFrame("Paint in binary");
        screen = new Screen();

        // Drawing panel
        JPanel panel = new JPanel() {
            @Override
            public void paintComponent(Graphics g) {
                super.paintComponent(g);
                g.setColor(Color.BLACK);
                g.fillRect(0, 0, pixelsH * pixelSize, pixelsV * pixelSize);

                screen.render(g);

                g.setColor(Color.GRAY);
                for (int i = 0; i < pixelsH; i++) {
                    int x = i * pixelSize;
                    g.drawLine(x, 0, x, pixelsV * pixelSize);
                }
                for (int i = 0; i < pixelsV; i++) {
                    int y = i * pixelSize;
                    g.drawLine(0, y, pixelsH * pixelSize, y);
                }

                g.setColor(Color.RED);

                g.drawLine(mouseX - 10, mouseY, mouseX + 10, mouseY);
                g.drawLine(mouseX, mouseY - 10, mouseX, mouseY + 10);
                repaint();
            }
        };

        setup(frame, panel);

    }

    private void setup(JFrame frame, JPanel panel) {

        /* Set up panel */
        panel.setPreferredSize(new Dimension(pixelsH * pixelSize, pixelsV * pixelSize));

        /* Set up frame */
        //frame.setLayout(new FlowLayout(FlowLayout.RIGHT, 0, 0));
        GridBagLayout layout = new GridBagLayout();
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.fill = GridBagConstraints.HORIZONTAL;
        frame.setLayout(layout);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.add(panel, constraints);
        frame.setResizable(true);

        JTextField jtfIO = new JTextField("0, 0, 0, 0, 0, 0, 0, 0, ");
        jtfIO.addActionListener(e -> {
            if (e.getActionCommand().length() > 0) {
                if (!screen.setPixels(jtfIO.getText()))
                    jtfIO.setText(screen.getPixelsDecimalString());
            }
        });

        frame.add(jtfIO, constraints);

        frame.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {

            }

            @Override
            public void mousePressed(MouseEvent e) {
                Point p = MouseInfo.getPointerInfo().getLocation();
                SwingUtilities.convertPointFromScreen(p, panel);
                mouseX = p.x;
                mouseY = p.y;
                int x = mouseX / Main.pixelSize;
                int y = mouseY / Main.pixelSize;

                screen.setPixel(x, y, e.getButton() == MouseEvent.BUTTON1);
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                jtfIO.setText(screen.getPixelsDecimalString());
            }

            @Override
            public void mouseEntered(MouseEvent e) {

            }

            @Override
            public void mouseExited(MouseEvent e) {

            }
        });

        frame.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
                Point p = MouseInfo.getPointerInfo().getLocation();
                SwingUtilities.convertPointFromScreen(p, panel);
                mouseX = p.x;
                mouseY = p.y;
                int x = mouseX / Main.pixelSize;
                int y = mouseY / Main.pixelSize;

                screen.setPixel(x, y, SwingUtilities.isLeftMouseButton(e));
            }

            @Override
            public void mouseMoved(MouseEvent e) {
                Point p = MouseInfo.getPointerInfo().getLocation();
                SwingUtilities.convertPointFromScreen(p, panel);
                mouseX = p.x;
                mouseY = p.y;
            }
        });

        /* Finish set up */
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new Main();
    }

}
