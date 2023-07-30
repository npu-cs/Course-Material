class UserException extends Exception {
    private int idnumber;

    public UserException(String message, int id) {
        super(message);
        this.idnumber = id;
    }

    public int getId() {
        return idnumber;
    }
}

public class TestException {
    public void regist(int num) throws UserException {
        if (num < 0) {
            throw new UserException("人数为负值，不合理", 3);
        }
        System.out.println("登记人数" + num);
    }

    public void manager() {
        try {
            regist(-100);
        } catch (UserException e) {
            System.out.println("登记出错，类别:" + e.getId());
        }
        System.out.println("本次登记操作结束");
    }

    public static void main(String[] args) {
        TestException t = new TestException();
        t.manager();
    }
}