#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


class Playerdialog : public QDialog{
    Q_OBJECT

public:

    //////////////////////// Constructor / Destructor /////////////////////

    Playerdialog();
    virtual ~Playerdialog();

    ////////////////////// Getters ////////////////////////////////////////

    QString getPlayername() const;

private slots:

    void slot_validated();

private:

    QLineEdit* playernameedit;
    QString playername;

};

#endif // PLAYERDIALOG_H
