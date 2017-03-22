#ifndef NEWSERVER_H
#define NEWSERVER_H

#include <QDialog>
#include <QMessageBox>
#include <serialcom.h>

namespace Ui {
class NewServer;
}

class NewServer : public QDialog
{
    Q_OBJECT

public:
    explicit NewServer(QWidget *parent = 0);
    ~NewServer();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewServer *ui;
};

#endif // NEWSERVER_H
