import java.awt.Graphics;

import java.applet.Applet;

public class MyFirstJavaApplet extends Applet {
	public String s;

	public void init() {
		s = new String("Hello World!");
	}

	public void paint(Graphics g) {
		g.drawString(s, 25, 25);
	}
}