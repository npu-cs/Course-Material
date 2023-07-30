class Book {
	String Title;
	String Pdata;
	int Words;

	Book(String Title, String Pdata, int Words) {
		this.Title = Title;
		this.Pdata = Pdata;
		this.Words = Words;
	}

	double getPrice() {
		String[] str = Pdata.split("-");
		int month = Integer.parseInt(str[1]);
		if (month <= 6)
			return 1.2 * Words / 1000 * 35;
		else
			return 1.18 * Words / 1000 * 35;
	}

	String getTitle() {
		return Title;
	}

	String getPdata() {
		return Pdata;
	}

	int getWords() {
		return Words;
	}
}