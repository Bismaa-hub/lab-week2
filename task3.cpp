#include <iostream>
#include <string>
using namespace std;
class Publication {
public:
	virtual void display() const = 0; 
	virtual string getIdentifier() const = 0; 
	virtual ~Publication() = default; 
};
class Book : public Publication {
private:
	string title;
	string author;
	int pages;

public:
	Book(const string& title, const string& author, int pages)
		: title(title), author(author), pages(pages) {}

	void display() const override {
		cout << "Book: " << title << " by " << author << ", Pages: " << pages << endl;
	}

	string getIdentifier() const override {
		return title; 
	}

	int getPages() const {
		return pages;
	}
};
class Newspaper : public Publication {
private:
	string name;
	string date;
	string edition;

public:
	Newspaper(const string& name, const string& date, const string& edition)
		: name(name), date(date), edition(edition) {}

	void display() const override {
		cout << "Newspaper: " << name << ", Date: " << date << ", Edition: " << edition << endl;
	}

	string getIdentifier() const override {
		return name; 
	}

	string getEdition() const {
		return edition;
	}
};
class Library {
private:
	Publication* collection[100]; 
	int count; 

public:
	Library() : count(0) {}
	~Library() {
		for (int i = 0; i < count; ++i) {
			delete collection[i]; 
		}
	}

	void addBook(const Book& book) {
		if (count < 100) {
			collection[count++] = new Book(book); 
		}
	}

	void addNewspaper(const Newspaper& newspaper) {
		if (count < 100) {
			collection[count++] = new Newspaper(newspaper); 
		}
	}

	void displayCollection() const {
		for (int i = 0; i < count; ++i) {
			collection[i]->display();
		}
	}

	void sortBooksByPages() {
		for (int i = 0; i < count - 1; ++i) {
			for (int j = 0; j < count - i - 1; ++j) {
				if (Book* bookA = dynamic_cast<Book*>(collection[j])) {
					if (Book* bookB = dynamic_cast<Book*>(collection[j + 1])) {
						if (bookA->getPages() > bookB->getPages()) {
							Publication* temp = collection[j];
							collection[j] = collection[j + 1];
							collection[j + 1] = temp;
						}
					}
				}
			}
		}
	}

	void sortNewspapersByEdition() {
		for (int i = 0; i < count - 1; ++i) {
			for (int j = 0; j < count - i - 1; ++j) {
				if (Newspaper* newsA = dynamic_cast<Newspaper*>(collection[j])) {
					if (Newspaper* newsB = dynamic_cast<Newspaper*>(collection[j + 1])) {
						if (newsA->getEdition() > newsB->getEdition()) {
	
							Publication* temp = collection[j];
							collection[j] = collection[j + 1];
							collection[j + 1] = temp;
						}
					}
				}
			}
		}
	}

	Book* searchBookByTitle(const string& title) {
		for (int i = 0; i < count; ++i) {
			if (Book* book = dynamic_cast<Book*>(collection[i])) {
				if (book->getIdentifier() == title) {
					return book;
				}
			}
		}
		return nullptr;
	}
	Newspaper* searchNewspaperByName(const string& name) {
		for (int i = 0; i < count; ++i) {
			if (Newspaper* news = dynamic_cast<Newspaper*>(collection[i])) {
				if (news->getIdentifier() == name) {
					return news;
				}
			}
		}
		return nullptr;
	}
};
int main() {
	Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
	Book book2("To Kill a Mockingbird", "Harper Lee", 324);
	Newspaper newspaper1("Washington Post", "2024-10-13", "Morning Edition");
	Newspaper newspaper2("The Times", "2024-10-12", "Weekend Edition");
	Library library;
	library.addBook(book1);
	library.addBook(book2);
	library.addNewspaper(newspaper1);
	library.addNewspaper(newspaper2);

	cout << "Before Sorting:<<endl;";
	library.displayCollection();
	library.sortBooksByPages();
	library.sortNewspapersByEdition();

	cout << "After Sorting:<<endl;";
	library.displayCollection();
	Book* foundBook = library.searchBookByTitle("The Catcher in the Rye");
	if (foundBook) {
		cout << "Found Book:<<endl;";
		foundBook->display();
	}
	else {
		cout << "Book not found.<<endl;";
	}
	Newspaper* foundNewspaper = library.searchNewspaperByName("The Times");
	if (foundNewspaper) {
		cout << "Found Newspaper:<<endl;";
		foundNewspaper->display();
	}
	else {
		cout << "Newspaper not found.<<endl;";
	}

	return 0;
}

