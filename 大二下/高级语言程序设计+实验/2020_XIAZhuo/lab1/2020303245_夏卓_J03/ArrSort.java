import java.util.Scanner;

public class ArrSort {
	public static void main(String args[]) {
		int arr[] = { 10, 20, -9, 8, 98 };
		for (int i = 0; i < 5; i++)
			for (int j = i + 1; j < 5; j++) {
				if (arr[i] > arr[j]) {
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}

		for (int i = 0; i < 5; i++)
			System.out.print(arr[i] + " ");
		System.out.println("");

		System.out.println("请输入数组中的一个元素:");
		Scanner scanner = new Scanner(System.in);
		boolean flag = false;
		while (flag == false) {
			int a1 = scanner.nextInt();
			int i;
			for (i = 0; i < 5; i++) {
				if (arr[i] == a1) {
					flag = true;
					break;
				}
			}
			if (flag)
				System.out.println(a1 + "在数组中的下标为:" + i);
			else
				System.out.println(a1 + "不在数组中，请重新输入:");
		}
	}
}