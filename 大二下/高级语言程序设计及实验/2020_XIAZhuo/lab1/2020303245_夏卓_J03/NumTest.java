public class NumTest {
	public static void main(String args[]) {
		int n, num, num1;
		System.out.println("在1~1000可被3与7整除的为");
		for (n = 1; n <= 1000; n++) {
			num = n % 3;
			num1 = n % 7;
			if (num == 0 && num1 == 0) {
				System.out.print(n + " ");
			}
		}
		System.out.println("");
	}
}
