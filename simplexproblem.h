#ifndef SIMPLEXPROBLEM_H
#define SIMPLEXPROBLEM_H

#include <QDialog>

namespace Ui {
    class SimplexProblem;
}

class SimplexProblem : public QDialog
{
    Q_OBJECT

public:
    explicit SimplexProblem(QWidget *parent = 0);
    ~SimplexProblem();

private:
    Ui::SimplexProblem *ui;


private slots:
    void on_genrerateMatrixButton_clicked();
    void on_SimplexSolveButton_clicked();

};






#endif // SIMPLEXPROBLEM_H
