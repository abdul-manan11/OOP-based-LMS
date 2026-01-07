#include "person.h"

Person::Person()
    : personId(""), personName(""), personEmail(""), personPassword(""), personDateOfBirth(QDate::currentDate()) {}

Person::Person(QString id, QString name, QString email, QString password, QDate dob)
    : personId(id), personName(name), personEmail(email), personPassword(password), personDateOfBirth(dob) {}

QString Person::getId() const { return personId; }
QString Person::getName() const { return personName; }
QString Person::getEmail() const { return personEmail; }
QString Person::getPassword() const { return personPassword; }
QDate Person::getDateOfBirth() const { return personDateOfBirth; }

void Person::setId(QString id) { personId = id; }
void Person::setName(QString name) { personName = name; }
void Person::setEmail(QString email) { personEmail = email; }
void Person::setPassword(QString password) { personPassword = password; }
void Person::setDateOfBirth(QDate dob) { personDateOfBirth = dob; }

Person::~Person() {}
