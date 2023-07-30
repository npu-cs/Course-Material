public class TestClass {
	public static void main(String args[]) {
		Book[] books = { new Book("Study Java", "2022-4-1", 102230), new Book("Study C++", "2021-8-30", 10200) };
		System.out.println("Title\t\tPdata\t\tWords\t\tPrice");
		for (Book book : books) {
			System.out.print(book.getTitle() + "\t");
			System.out.print(book.getPdata() + "\t");
			System.out.print(book.getWords() + "\t");
			System.out.println("\t" + book.getPrice());
		}
	}
}