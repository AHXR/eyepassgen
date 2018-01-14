/*
    @title
        eyepassgen
    @author
        AHXR (https://github.com/AHXR)
    @copyright
        2017

    eyepassgen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    eyepassgen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with eyepassgen.  If not, see <http://www.gnu.org/licenses/>.
*/
//=======================================================
#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>

namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_btnGenerate_released();

    void on_horizontalSlider_valueChanged(int value);

    void updateGenerateAmount( unsigned short amount );
    void on_lstPasswords_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::window *ui;
};

#endif // WINDOW_H
