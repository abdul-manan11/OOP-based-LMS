#include "database.h"
#include "filehandler.h"
#include "student.h"    // Added
#include "faculty.h"    // Added
#include "admin.h"      // Added
#include "course.h"     // Added
#include "person.h"     // Added if needed for Person base class
#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QDebug>
#include <QDate>

Database* Database::instance = nullptr;

Database::Database() {
    // Load data when database is created
    loadAllData();
}

Database* Database::getInstance() {
    if (!instance) {
        instance = new Database();
    }
    return instance;
}

// STUDENT METHODS
void Database::addStudent(Student* student) {
    students[student->getId()] = student;
}

void Database::removeStudent(QString studentId) {
    if (students.contains(studentId)) {
        delete students[studentId];
        students.remove(studentId);
    }
}

Student* Database::getStudent(QString studentId) {
    return students.value(studentId, nullptr);
}

QVector<Student*> Database::getAllStudents() {
    QVector<Student*> studentList;
    for (auto student : students) {
        studentList.append(student);
    }
    return studentList;
}

// FACULTY METHODS
void Database::addFaculty(Faculty* faculty) {
    faculties[faculty->getId()] = faculty;
}

void Database::removeFaculty(QString facultyId) {
    if (faculties.contains(facultyId)) {
        delete faculties[facultyId];
        faculties.remove(facultyId);
    }
}

Faculty* Database::getFaculty(QString facultyId) {
    return faculties.value(facultyId, nullptr);
}

QVector<Faculty*> Database::getAllFaculty() {
    QVector<Faculty*> facultyList;
    for (auto faculty : faculties) {
        facultyList.append(faculty);
    }
    return facultyList;
}

// ADMIN METHODS
void Database::addAdmin(Admin* admin) {
    admins[admin->getId()] = admin;
}

Admin* Database::getAdmin(QString adminId) {
    return admins.value(adminId, nullptr);
}

// COURSE METHODS
void Database::addCourse(Course* course) {
    courses[course->getCourseCode()] = course;
}

void Database::removeCourse(QString courseCode) {
    if (courses.contains(courseCode)) {
        delete courses[courseCode];
        courses.remove(courseCode);
    }
}

Course* Database::getCourse(QString courseCode) {
    return courses.value(courseCode, nullptr);
}

QVector<Course*> Database::getAllCourses() {
    QVector<Course*> courseList;
    for (auto course : courses) {
        courseList.append(course);
    }
    return courseList;
}

// AUTHENTICATION
Person* Database::authenticateUser(QString email, QString password, QString role) {
    if (role == "Student") {
        for (auto student : students) {
            if (student->getEmail() == email && student->getPassword() == password) {
                return student;
            }
        }
    } else if (role == "Faculty") {
        for (auto faculty : faculties) {
            if (faculty->getEmail() == email && faculty->getPassword() == password) {
                return faculty;
            }
        }
    } else if (role == "Admin") {
        for (auto admin : admins) {
            if (admin->getEmail() == email && admin->getPassword() == password) {
                return admin;
            }
        }
    }
    return nullptr;
}

// SAVE ALL DATA
void Database::saveAllData() {
    QDir().mkpath("data");

    // Save students
    QFile studentFile("data/students.dat");
    if (studentFile.open(QIODevice::WriteOnly)) {
        QDataStream out(&studentFile);
        out.setVersion(QDataStream::Qt_5_15);

        out << (qint32)students.size();
        for (auto student : students) {
            // Save basic student info
            FileHandler::writeString(out, student->getId());
            FileHandler::writeString(out, student->getRollNumber());
            FileHandler::writeString(out, student->getName());
            FileHandler::writeString(out, student->getEmail());
            FileHandler::writeString(out, student->getPassword());

            QDate dob = student->getDateOfBirth();
            out << dob;

            FileHandler::writeString(out, student->getDepartment());
            out << (qint32)student->getSemester();

            // Save grades
            QMap<QString, double> grades = student->getCourseGrades();
            out << (qint32)grades.size();
            for (auto it = grades.begin(); it != grades.end(); ++it) {
                FileHandler::writeString(out, it.key());
                out << it.value();
            }

            // Save attendance
            QMap<QString, double> attendance = student->getCourseAttendance();
            out << (qint32)attendance.size();
            for (auto it = attendance.begin(); it != attendance.end(); ++it) {
                FileHandler::writeString(out, it.key());
                out << it.value();
            }
        }
        studentFile.close();
    }

    // Save faculty
    QFile facultyFile("data/faculty.dat");
    if (facultyFile.open(QIODevice::WriteOnly)) {
        QDataStream out(&facultyFile);
        out.setVersion(QDataStream::Qt_5_15);

        out << (qint32)faculties.size();
        for (auto faculty : faculties) {
            FileHandler::writeString(out, faculty->getId());
            FileHandler::writeString(out, faculty->getName());
            FileHandler::writeString(out, faculty->getEmail());
            FileHandler::writeString(out, faculty->getPassword());

            QDate dob = faculty->getDateOfBirth();
            out << dob;

            FileHandler::writeString(out, faculty->getDepartment());
            FileHandler::writeString(out, faculty->getDesignation());
        }
        facultyFile.close();
    }

    // Save courses
    QFile courseFile("data/courses.dat");
    if (courseFile.open(QIODevice::WriteOnly)) {
        QDataStream out(&courseFile);
        out.setVersion(QDataStream::Qt_5_15);

        out << (qint32)courses.size();
        for (auto course : courses) {
            FileHandler::writeString(out, course->getCourseCode());
            FileHandler::writeString(out, course->getCourseName());
            FileHandler::writeString(out, course->getCourseDescription());
            FileHandler::writeString(out, course->getFacultyId());
            out << (qint32)course->getCreditHours();

            // Save lecture materials
            QVector<QString> lectures = course->getLectureMaterials();
            out << (qint32)lectures.size();
            for (const QString& lecture : lectures) {
                FileHandler::writeString(out, lecture);
            }
        }
        courseFile.close();
    }

    // Save admin
    QFile adminFile("data/admin.dat");
    if (adminFile.open(QIODevice::WriteOnly)) {
        QDataStream out(&adminFile);
        out.setVersion(QDataStream::Qt_5_15);

        out << (qint32)admins.size();
        for (auto admin : admins) {
            FileHandler::writeString(out, admin->getId());
            FileHandler::writeString(out, admin->getName());
            FileHandler::writeString(out, admin->getEmail());
            FileHandler::writeString(out, admin->getPassword());

            QDate dob = admin->getDateOfBirth();
            out << dob;

            FileHandler::writeString(out, admin->getDepartment());
        }
        adminFile.close();
    }

    qDebug() << "All data saved successfully!";
}

// LOAD ALL DATA
void Database::loadAllData() {
    // Clear existing data
    students.clear();
    faculties.clear();
    courses.clear();
    admins.clear();

    // Load students
    QFile studentFile("data/students.dat");
    if (studentFile.open(QIODevice::ReadOnly)) {
        QDataStream in(&studentFile);
        in.setVersion(QDataStream::Qt_5_15);

        qint32 studentCount;
        in >> studentCount;

        for (int i = 0; i < studentCount; ++i) {
            QString id = FileHandler::readString(in);
            QString roll = FileHandler::readString(in);
            QString name = FileHandler::readString(in);
            QString email = FileHandler::readString(in);
            QString password = FileHandler::readString(in);

            QDate dob;
            in >> dob;

            QString department = FileHandler::readString(in);
            qint32 semester;
            in >> semester;

            Student* student = new Student(id, roll, name, email, password, dob, department, semester);

            // Load grades
            qint32 gradeCount;
            in >> gradeCount;
            for (int j = 0; j < gradeCount; ++j) {
                QString courseCode = FileHandler::readString(in);
                double grade;
                in >> grade;
                student->addGrade(courseCode, grade);
            }

            // Load attendance
            qint32 attendanceCount;
            in >> attendanceCount;
            for (int j = 0; j < attendanceCount; ++j) {
                QString courseCode = FileHandler::readString(in);
                double attendance;
                in >> attendance;
                student->addAttendance(courseCode, attendance);
            }

            students[id] = student;
        }
        studentFile.close();
        qDebug() << "Loaded" << students.size() << "students";
    }

    // Load faculty
    QFile facultyFile("data/faculty.dat");
    if (facultyFile.open(QIODevice::ReadOnly)) {
        QDataStream in(&facultyFile);
        in.setVersion(QDataStream::Qt_5_15);

        qint32 facultyCount;
        in >> facultyCount;

        for (int i = 0; i < facultyCount; ++i) {
            QString id = FileHandler::readString(in);
            QString name = FileHandler::readString(in);
            QString email = FileHandler::readString(in);
            QString password = FileHandler::readString(in);

            QDate dob;
            in >> dob;

            QString department = FileHandler::readString(in);
            QString designation = FileHandler::readString(in);

            Faculty* faculty = new Faculty(id, name, email, password, dob, department, designation);
            faculties[id] = faculty;
        }
        facultyFile.close();
        qDebug() << "Loaded" << faculties.size() << "faculty";
    }

    // Load courses
    QFile courseFile("data/courses.dat");
    if (courseFile.open(QIODevice::ReadOnly)) {
        QDataStream in(&courseFile);
        in.setVersion(QDataStream::Qt_5_15);

        qint32 courseCount;
        in >> courseCount;

        for (int i = 0; i < courseCount; ++i) {
            QString code = FileHandler::readString(in);
            QString name = FileHandler::readString(in);
            QString description = FileHandler::readString(in);
            QString facultyId = FileHandler::readString(in);
            qint32 credits;
            in >> credits;

            Course* course = new Course(code, name, description, facultyId, credits);

            // Load lecture materials
            qint32 lectureCount;
            in >> lectureCount;
            for (int j = 0; j < lectureCount; ++j) {
                QString lecture = FileHandler::readString(in);
                course->addLectureMaterial(lecture);
            }

            courses[code] = course;
        }
        courseFile.close();
        qDebug() << "Loaded" << courses.size() << "courses";
    }

    // Load admin
    QFile adminFile("data/admin.dat");
    if (adminFile.open(QIODevice::ReadOnly)) {
        QDataStream in(&adminFile);
        in.setVersion(QDataStream::Qt_5_15);

        qint32 adminCount;
        in >> adminCount;

        for (int i = 0; i < adminCount; ++i) {
            QString id = FileHandler::readString(in);
            QString name = FileHandler::readString(in);
            QString email = FileHandler::readString(in);
            QString password = FileHandler::readString(in);

            QDate dob;
            in >> dob;

            QString department = FileHandler::readString(in);

            Admin* admin = new Admin(id, name, email, password, dob, department);
            admins[id] = admin;
        }
        adminFile.close();
    }

    // Add default admin if none exists
    if (admins.isEmpty()) {
        Admin* defaultAdmin = new Admin("admin1", "System Admin", "admin@lms.com",
                                        "admin123", QDate(1980, 1, 1), "Administration");
        addAdmin(defaultAdmin);
        saveAllData(); // Save the default admin
        qDebug() << "Created default admin";
    }

    // Add some default data if database is empty (for testing)
    if (students.isEmpty() && faculties.isEmpty() && courses.isEmpty()) {
        createDefaultData();
    }
}

// CREATE DEFAULT DATA FOR TESTING
void Database::createDefaultData() {
    qDebug() << "Creating default data...";

    // Create some default students
    Student* student1 = new Student("S1001", "S1001", "Ali Ahmed", "ali@university.edu",
                                    "password123", QDate(2000, 5, 15), "Computer Science", 3);
    Student* student2 = new Student("S1002", "S1002", "Sara Khan", "sara@university.edu",
                                    "password123", QDate(2001, 8, 22), "Computer Science", 3);
    addStudent(student1);
    addStudent(student2);

    // Create some default faculty
    Faculty* faculty1 = new Faculty("F1001", "Dr. Ahmed Raza", "ahmed@university.edu",
                                    "password123", QDate(1975, 3, 10), "Computer Science", "Professor");
    Faculty* faculty2 = new Faculty("F1002", "Dr. Fatima Ali", "fatima@university.edu",
                                    "password123", QDate(1980, 11, 5), "Computer Science", "Associate Professor");
    addFaculty(faculty1);
    addFaculty(faculty2);

    // Create some default courses
    Course* course1 = new Course("CS101", "Introduction to Programming",
                                 "Basic programming concepts using C++", "F1001", 3);
    Course* course2 = new Course("CS201", "Data Structures",
                                 "Fundamental data structures and algorithms", "F1002", 3);
    addCourse(course1);
    addCourse(course2);

    // Add sample data
    student1->addGrade("CS101", 85.5);
    student1->addAttendance("CS101", 92.0);
    student2->addGrade("CS101", 78.0);
    student2->addAttendance("CS101", 88.5);

    // Register students to courses
    student1->registerCourse(course1);
    student2->registerCourse(course1);
    student1->registerCourse(course2);

    // Add some lecture materials
    course1->addLectureMaterial("lectures/cs101_lecture1.pdf");
    course1->addLectureMaterial("lectures/cs101_lecture2.pdf");
    course2->addLectureMaterial("lectures/cs201_lecture1.pptx");

    // Save all default data
    saveAllData();
    qDebug() << "Default data created and saved!";
}

Database::~Database() {
    // Save data before destruction
    saveAllData();

    // Cleanup all pointers
    for (auto student : students) delete student;
    for (auto faculty : faculties) delete faculty;
    for (auto admin : admins) delete admin;
    for (auto course : courses) delete course;

    students.clear();
    faculties.clear();
    admins.clear();
    courses.clear();
}
