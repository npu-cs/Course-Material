import java.io.*;

public class MyClass {
	private int val1, val2;

	public void myFun(int x, int y) {
		val1 = x;
		val2 = y;
		System.out.println("the sum is " + (val1 + val2));
	}

	public static void main(String arg[]) {
		MyClass MyObj = new MyClass();
		MyObj.myFun(3, 4);
	}
}