#ifndef LEVELCHANGEDIALOG_H
#define LEVELCHANGEDIALOG_H

#include <QDialog>

namespace Ui
{
class LevelChangeDialog;
}

class LevelChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelChangeDialog(QWidget* parent = nullptr);
    ~LevelChangeDialog() override;

private:
    Ui::LevelChangeDialog* ui;
};

#endif // LEVELCHANGEDIALOG_H
