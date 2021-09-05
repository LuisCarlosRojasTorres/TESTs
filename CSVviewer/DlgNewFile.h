#ifndef DLGNEWFILE_H
#define DLGNEWFILE_H

#include <QDialog>

namespace Ui {
class DlgNewFile;
}

class DlgNewFile : public QDialog
{
    Q_OBJECT

public:
    explicit DlgNewFile(QWidget *parent = nullptr);
    ~DlgNewFile();

    int getRowCount() const;
    int getColumnCount() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DlgNewFile *ui;
};

#endif // DLGNEWFILE_H
