public class Application {
    public static void main(String[] args) {
        Student[] students = { new Student("张一"), new Student("李二"), new Student("赵三") };

        students[0].courses = new Course[] { new Course("数学", 4, 71.5),
                new Course("英语", 3.5, 80.4),
                new Course("数据结构", 3, 95.5) };

        students[1].courses = new Course[] { new Course("数学", 4, 78.5),
                new Course("数据结构", 3, 54.5),
                new Course("数据库", 3, 60.5) };

        students[2].courses = new Course[] { new Course("数学", 4, 88.5),
                new Course("英语", 3.5, 92.5),
                new Course("数据结构", 3, 71.5) };

        for (Student student : students)
            System.out.println(student.getName() + "的GPA为:" + student.getGPA());
    }
}