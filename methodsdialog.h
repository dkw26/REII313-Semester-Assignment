#ifndef METHODSDIALOG_H
#define METHODSDIALOG_H
#include <simplexproblem.h>
#include <bnbproblem.h>
#include <QDialog>

namespace Ui {
    class MethodsDialog;
}

class MethodsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MethodsDialog(QWidget *parent = 0);
    ~MethodsDialog();

private:
    Ui::MethodsDialog *ui;
    SimplexProblem *simplexProblem;
    BnBProblem *bnbProblem;

private slots:


private slots:

    void on_BnBButton_clicked();
    void on_SimplexButton_clicked();
};

#endif // METHODSDIALOG_H
