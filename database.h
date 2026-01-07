#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include <QVector>
#include <QString>

// Forward declarations
class Student;
class Faculty;
class Admin;
class Course;
class Person;

class Database {
private:
    static Database* instance;

    QMap<QString, Student*> students;
    QMap<QString, Faculty*> faculties;
    QMap<QString, Admin*> admins;
    QMap<QString, Course*> courses;

    Database();

public:
    static Database* getInstance();

    // Student methods
    void addStudent(Student* student);
    void removeStudent(QString studentId);
    Student* getStudent(QString studentId);
    QVector<Student*> getAllStudents();

    // Faculty methods
    void addFaculty(Faculty* faculty);
    void removeFaculty(QString facultyId);
    Faculty* getFaculty(QString facultyId);
    QVector<Faculty*> getAllFaculty();

    // Admin methods
    void addAdmin(Admin* admin);
    Admin* getAdmin(QString adminId);

    // Course methods
    void addCourse(Course* course);
    void removeCourse(QString courseCode);
    Course* getCourse(QString courseCode);
    QVector<Course*> getAllCourses();

    // Authentication
    Person* authenticateUser(QString email, QString password, QString role);

    // Data persistence methods
    void saveAllData();
    void loadAllData();
    void createDefaultData();

    // Destructor
    ~Database();

    // Prevent copying
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};

#endif // DATABASE_H
