class Course {
	String name;
	double credit;
	double score;

	Course(String name, double credit, double score) {
		this.name = name;
		this.credit = credit;
		this.score = score;
	}

	public double getGrade() {
		if (score >= 85)
			return 4;
		else if (score >= 75)
			return 3;
		else if (score >= 60)
			return 2;
		else if (score >= 45)
			return 1;
		else
			return 0;
	}

	public String getName() {
		return name;
	}

	public double getCredit() {
		return credit;
	}

	public double getscore() {
		return score;
	}
}

public class Student {
	String name;
	Course[] courses;

	Student(String name) {
		this.name = name;
	}

	public double getGPA() {
		double gradeSum = 0, creditSum = 0;
		for (Course course : courses) {
			gradeSum += course.getGrade() * course.getCredit();
			creditSum += course.getCredit();
		}
		return gradeSum / creditSum;
	}

	public String getName() {
		return name;
	}
}