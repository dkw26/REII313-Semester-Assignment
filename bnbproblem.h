#ifndef BNBPROBLEM_H
#define BNBPROBLEM_H



#include <QDialog>

namespace Ui {
    class BnBProblem;
}

class BnBProblem : public QDialog
{
    Q_OBJECT

public:
    explicit BnBProblem(QWidget *parent = 0);
    ~BnBProblem();

private:
    Ui::BnBProblem *ui;


private slots:

private slots:
    void on_BnBSolveButton_clicked();
    void on_bnbGenerateButton_clicked();
};

#endif // BNBPROBLEM_H
