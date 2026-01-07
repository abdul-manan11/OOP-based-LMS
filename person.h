#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>

class Person {
protected:
    QString personId;
    QString personName;
    QString personEmail;
    QString personPassword;
    QDate personDateOfBirth;

public:
    Person();
    Person(QString id, QString name, QString email, QString password, QDate dob);

    // Pure virtual functions (Abstraction)
    virtual void displayInfo() = 0;
    virtual QString getRole() = 0;

    // Getter methods
    QString getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getPassword() const;
    QDate getDateOfBirth() const;

    // Setter methods
    void setId(QString id);
    void setName(QString name);
    void setEmail(QString email);
    void setPassword(QString password);
    void setDateOfBirth(QDate dob);

    virtual ~Person();
};

#endif // PERSON_H
