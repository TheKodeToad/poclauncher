#pragma once

#include <QMainWindow>

class QEvent;
class QMainMenu;
class QWidget;

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
    void retranslate();
    void setToolbarsLocked(bool locked);

    Ui::MainWindow* m_ui;
};
