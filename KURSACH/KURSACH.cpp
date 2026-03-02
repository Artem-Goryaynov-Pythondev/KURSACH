#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Student
{
private:
    string full_name;
    int year_of_admission;
    string group;
    string grade_book_number;
    string institute;

public:
    Student() :year_of_admission(0) {}

    Student(string name, int year, string grp, string grade, string inst) {
        full_name = name;
        year_of_admission = year;
        group = grp;
        grade_book_number = grade;
        institute = inst;
    }
    string get_full_name() const { return full_name; }
    int get_year_of_admission() const { return year_of_admission; }
    string get_group() const { return group; }
    string get_grade_book_number() const { return grade_book_number; }
    string get_institute() const { return institute; }

    void set_full_name(string name) { full_name = name; }
    void set_year_of_admission(int year) { year_of_admission = year; }
    void set_group(string grp) { group = grp; }
    void set_grade_book_number(string grade) { grade_book_number = grade; }
    void set_institute(string inst) { institute = inst; }

    void display() const {
        cout << full_name << "|" << group << " | зач.#" << grade_book_number << endl;
    }
};

class Book
{

private:
    string author;
    int inventory_number;
    string name;
    string takenBy;
    string takenDate;
    string returnDate;
    string status;

public:
    Book() :inventory_number(0) {}
    Book(string aut, int number, string nam, string tb = "", string td = "", string rd = "", string sta) {
        author = aut;
        inventory_number = number;
        name = nam;
        takenBy = tb;
        takenDate = td;
        returnDate = rd;
        status = sta;
    }

    string get_author() const { return author; }
    int get_inventory_number() const { return inventory_number; }
    string get_name() const { return name; }
    string get_takenBy() const { return takenBy; }
    string get_returnDate() const { return returnDate; }
    string get_status() const { return status; }

    void set_author(string aut) { author = aut; }
    void set_inventory_number(int num) { inventory_number = num; }
    void set_name(string nam) { name = nam; }
    void set_takenBy(string tb) { takenBy = tb; }
    void set_takenDate(string td) { takenDate = td; }
    void set_status(string sta) { status = sta; }

    void display() const {
        cout << inventory_number << " | " << author << " | " << name << " | " << status;
        if (status == "на руках") {
            cout << " | Взял: " << takenBy << " | до " << returnDate;

        }
        cout << endl;
    }

};

class Transactions {
private:
    string type;
    int inventory_number;
    string name;
    string date;
    string bib_name;

public:
    Transactions() : inventory_number(0) {}
    Transactions(string typ, int inv, string nam, string dat, string bib) {
        type = typ;
        inventory_number = inv;
        name = nam;
        date = dat;
        bib = bib_name;
    }

    string get_type() const { return type; }
    int get_inventory_number() const { return inventory_number; }
    string get_name() const { return name; }
    string get_date() const { return date; }
    string get_bib_name() const { return bib_name; }

    void display() const {
        cout << "Книга с кодом " << inventory_number << " была взята студентом " << name << " датировано " << date << " и проконтролированно " << bib_name << endl;
    }
};


vector<string> split(const string& s, char delimiter) { // создаем vector<string> функцию split, которая принимает неизменяемую строку s и разделитель delimiter по которому будет резать s
    vector<string> tokens; // создаем вектор tokens который будеи хранить части на которые разбивается строка
    string token; // строка для временного хранения
    istringstream tokenStream(s); // создает tokenStream который берет s и делает с помошью istringstream строковый поток ввода 
    while (getline(tokenStream, token, delimiter)) { // функция getline читающая из потока tokenStream до разделителя delimiter и сохраняющая прочитанное 
        tokens.push_back(token); // добавляем то что разделилось в конец вектора tokens
    }
    return tokens;
}
//пошло говно по трубам, начинаю парсить бд
vector<Student> loadStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;
        vector<string> parts = split(line, '|');

        
            Student student;
            student.set_full_name(parts[0]);
            student.set_year_of_admission(stoi(parts[1]));
            student.set_group(parts[2]);
            student.set_grade_book_number(parts[3]);
            student.set_institute(parts[4]);

            students.push_back(student);
       
    }

    file.close();
    return students;
}

vector<Book> loadBooksFromFile(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;
        vector<string> parts = split(line, '|');
        
        Book book;
        book.set_author(parts[0]);
        book.set_inventory_number(stoi(parts[1]));
        book.set_name(parts[2]);
        book.set_takenBy(parts[3]);
        book.set_takenDate(parts[4]);
        book.set_status(parts[5]);

        books.push_back(book);
    }
    file.close();
    return books;

}

vector<Transactions> loadTransactionsFromFile(const string& filename) {
    vector<Transactions> transactions;
    ifstream file(filename);
    string line;
    int lineNumber = 0;
    while (getline(file, line)){
        lineNumber++;
        if (line.empty()) continue;
        vector<string> parts = split(line, '|');

        Transactions transaction(
            parts[0],
            stoi(parts[1]),
            parts[2],
            parts[3],
            parts[4]);

        transactions.push_back(transaction);
    }
    file.close();
    cout << "Загружено транзакций: " << transactions.size() << endl;
    return transactions;
}
    
