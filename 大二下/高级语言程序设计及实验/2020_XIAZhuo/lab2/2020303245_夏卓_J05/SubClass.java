package MainPackage;

class ParentClass {
    public int data;

    public ParentClass(int data) {
        this.data = data;
        System.out.println("data from ParentClass:" + data);
    }
}

public class SubClass extends ParentClass {
    public SubClass(int data) {
        super(data);
    }
}