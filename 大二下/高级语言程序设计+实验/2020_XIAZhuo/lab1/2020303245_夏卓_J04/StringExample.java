class StringExample {
    public static void main(String args[]) {
        String s1 = new String("you are a student"),
                s2 = new String("how are you");
        if (s1.equals(s2))
            System.out.println("s1与s2相同");
        else
            System.out.println("s1与s2不相同");

        String s3 = new String("22030219851022024");
        if (s3.startsWith("220302"))
            System.out.println("吉林省的身份证");

        String s4 = new String("你"),
                s5 = new String("我");
        if (s4.compareTo(s5) > 0)
            System.out.println("按字典序s4大于s5");
        else
            System.out.println("按字典序s4小于s5");

        int position = 0;
        String path = "c:\\java\\jsp\\A.java";
        position = path.lastIndexOf("\\");
        System.out.println("c:\\java\\jsp\\A.java中最后出现\\的位置:" + position);

        String fileName = path.substring(position + 1);
        System.out.println("c:\\java\\jsp\\A.java中含有的文件名:" + fileName);

        String s6 = new String("100"),
                s7 = new String("123.678");
        int n1 = Integer.parseInt(s6);
        double n2 = Double.valueOf(s7.toString());
        double m = n1 + n2;
        System.out.println(m);

        String s8 = String.valueOf(m);
        position = s8.indexOf(".");
        String temp = s8.substring(position + 1);
        System.out.println("数字" + m + "有" + temp.length() + "位小数");

        String s9 = new String("ABCDEF");
        char a[] = s9.toCharArray();
        for (int i = a.length - 1; i >= 0; i--) {
            System.out.print(" " + a[i]);
        }
    }
}
