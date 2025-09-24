#pragma once

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
   public:
    MainWindow(QWidget* parent = nullptr);

    void changeEvent(QEvent* event) override;

   protected:
    QMenu* createPopupMenu() override;

   private:
    void postRetranslate();
    void setToolbarsLocked(bool locked);

    Ui::MainWindow* m_ui;
};
