import java.util.Scanner;

public class StringToNum {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        try {
            if (str.indexOf(".") == -1) {
                int num = Integer.parseInt(str);
                System.out.println("已成功转化为int型数据:" + num);
            } else {
                double num = Double.parseDouble(str);
                System.out.println("已成功转化为double型数据:" + num);
            }
        } catch (NumberFormatException e) {
            System.out.println("含有非法字符输入");
        } finally {
            System.out.println("转换结束");
        }
    }
}