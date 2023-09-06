interface Vehicle {
    public void start(String name);

    public void stop(String name);
}

class Bike implements Vehicle {
    public void start(String name) {
        System.out.println("自行车从" + name + "出发");
    }

    public void stop(String name) {
        System.out.println("自行车在" + name + "停下");
    }
}

class Bus implements Vehicle {
    public void start(String name) {
        System.out.println("公交车从" + name + "出发");
    }

    public void stop(String name) {
        System.out.println("公交车在" + name + "停下");
    }
}

public class interfaceDemo {
    public static void main(String[] args) {
        Bike bike = new Bike();
        bike.start("宿舍楼");
        bike.stop("教学楼");
        Bus bus = new Bus();
        bus.start("西工大");
        bus.stop("市中心");
    }
}