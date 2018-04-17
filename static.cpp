#include "mainwindow.h"

//GUIDE
// INT -> QSTRING: setText(QString::number(patronSession->getUserlvl()));

//indexes
//0 - login
//1 - registration
//2 - menu user
//3 - profile
//4 - change user info
//5 - find book
//6 - discover book
//7 - show libraries
//8 - check out
//9 - admin functions
//10 - remove book
//11 - new admin
//12 - add book
//13 - add libary
//14 - menu admin
//15 - confirm order

//bool dbConnect() {
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("student.cs.hioa.no");
//    db.setDatabaseName("s315613");
//    db.setUserName("s315613");
//    db.setPassword("");

//    if (db.open()) {

//        return true;


//    } else {

//        return false;

//    }
//}

//PRINTE VERDIER FRA DB TIL GUI
//if (db.open()) {
//    QSqlQuery query("SELECT * FROM Library");
//    QString labelText;
//    while (query.next()) {

//        for(int i = 0; i <= query.size(); i++) {

//            labelText+=query.value(i).toString();

//        }

//    }
//    ui->label123->setText(labelText);


//} else {

//    ui->label123->setText("failed");

//}

//}
