import java.awt.*;

public class Screen {

    private boolean[][] rawPixels = new boolean[Main.pixelsV][Main.pixelsH];

    public void render(Graphics g) {
        g.setColor(Color.WHITE);
        for (int x = 0; x < Main.pixelsV; x++) {
            for (int y = 0; y < Main.pixelsH; y++) {
                if (rawPixels[x][Main.pixelsH - y - 1]) {
                    g.fillRect(x * Main.pixelSize + 4, y * Main.pixelSize + 4,
                            Main.pixelSize - 8, Main.pixelSize - 8);
                }
            }
        }
    }

    public void setPixels(int[] pixels) {
        for(int x = 0; x < pixels.length && x < rawPixels.length; x++) {
            String binaryString = Integer.toBinaryString(pixels[x]);
            char[] bits = String.format("%08d", Integer.parseInt(binaryString)).toCharArray();
            for(int y = 0; y < bits.length && y < rawPixels[x].length; y++) {
                rawPixels[x][y] = bits[y] == '1';
            }
        }
    }

    public boolean setPixels(String pixels) {
        try {
            pixels = pixels.replaceAll(" ", "");
            pixels = pixels.replaceAll("\t", "");
            pixels = pixels.replaceAll("\n", "");
            String[] bitString = pixels.split(",");
            int[] bits = new int[bitString.length];
            for (int i = 0; i < bitString.length; i++) {
                bits[i] = Integer.parseInt(bitString[i]);
            }
            setPixels(bits);
            return true;
        } catch(NumberFormatException e) {
            System.out.println("Format of string incorrect!");
            return false;
        }
    }

    public String getPixelsDecimalString() {
        StringBuilder sb = new StringBuilder();
        int[] decimals = getPixelsDecimal();
        for(int number : decimals) {
            sb.append(number);
            sb.append(", ");
        }
        return sb.toString();
    }

    public int[] getPixelsDecimal() {
        int[] decimals = new int[Main.pixelsV];
        for(int x = 0; x < Main.pixelsV; x++) {
            int number = 0;
            for(int y = 0; y < Main.pixelsH; y++) {
                if(rawPixels[x][Main.pixelsH - y - 1]) {
                    number += (int) Math.pow(2, y);
                }
            }
            decimals[x] = number;
        }
        return decimals;
    }

    public boolean[][] getPixelsBoolean() {
        return rawPixels.clone();
    }

    public void setPixel(int x, int y, boolean state) {
        if(x < 0 || y < 0 || x > Main.pixelsV - 1
                || y > Main.pixelsH - 1) return;
        rawPixels[x][Main.pixelsH - y - 1] = state;
    }

}
