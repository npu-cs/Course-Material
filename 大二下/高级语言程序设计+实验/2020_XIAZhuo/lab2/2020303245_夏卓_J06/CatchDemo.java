public class CatchDemo {
    public static void main(String[] args) {
        int number[] = { 4, 8, 16, 32, 64, 128, 256, 512 };
        int denom[] = { 2, 0, 4, 4, 0, 8 };
        for (int i = 0; i < number.length; i++) {
            try {
                System.out.println(number[i] + " / " + denom[i] + " is " +
                        number[i] / denom[i]);
            } catch (ArithmeticException exc) {
                System.out.println("Can't be divided by zero");
            } catch (ArrayIndexOutOfBoundsException exc) {
                System.out.println("No matching element found.");
            } finally {
                System.out.println("Finally 已执行");
            }
        }
    }
}