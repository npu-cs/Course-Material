class People {
    protected double weight, height;

    public void speakHello() {
        System.out.println("yayawawa");
    }

    public void averageHeight() {
        height = 173;
        System.out.println("average height:" + height);
    }

    public void averageWeight() {
        weight = 70;
        System.out.println("average weight:" + weight);
    }
}

class ChinaPeople extends People {

    public void speakHello() {
        System.out.println("你好，吃饭了吗？");
    }

    public void averageHeight() {
        height = 173.0;
        System.out.println("中国人的平均身高：" + height);
    }

    public void averageWeight() {
        weight = 67.34;
        System.out.println("中国人的平均体重：" + weight);
    }

    public void chinaGongfu() {
        System.out.println("坐如钟，站如松，睡如弓");
    }
}

class AmericanPeople extends People {
    public void speakHello() {
        System.out.println("How do you do?");
    }

    public void averageHeight() {
        height = 175.3;
        System.out.println("the average height of AmericanPeople is:" + height);
    }

    public void averageWeight() {
        weight = 69.8;
        System.out.println("the average weight of AmericanPeople is:" + weight);
    }

    public void americanBoxing() {
        System.out.println("直拳、勾拳");
    }
}

class BeijingPeople extends ChinaPeople {
    public void speakHello() {
        System.out.println("你好，这里是北京");
    }

    public void averageHeight() {
        height = 173.6;
        System.out.println("北京人的平均身高：" + height);
    }

    public void averageWeight() {
        weight = 68.23;
        System.out.println("北京人的平均体重：" + weight);
    }

    public void beijingOpera() {
        System.out.println("京剧术语");
    }
}

public class Example {
    public static void main(String[] args) {
        ChinaPeople chinaPeople = new ChinaPeople();
        AmericanPeople americanPeople = new AmericanPeople();
        BeijingPeople beijingPeople = new BeijingPeople();

        chinaPeople.speakHello();
        americanPeople.speakHello();
        beijingPeople.speakHello();

        chinaPeople.averageHeight();
        americanPeople.averageHeight();
        beijingPeople.averageHeight();

        chinaPeople.averageWeight();
        americanPeople.averageWeight();
        beijingPeople.averageWeight();

        chinaPeople.chinaGongfu();
        americanPeople.americanBoxing();
        beijingPeople.beijingOpera();
        beijingPeople.chinaGongfu();
    }
}