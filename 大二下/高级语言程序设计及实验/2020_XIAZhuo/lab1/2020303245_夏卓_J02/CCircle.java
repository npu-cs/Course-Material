class CCircle {
	final double pi = 3.14159;
	double radius;

	CCircle(double r) {
		radius = r;
	}
	
	void setCircle(double r) {     
		radius = r;
    }
	
	double getRadius() {
		return radius;
	}

	double getArea() {
		return pi * radius * radius;
	}
}