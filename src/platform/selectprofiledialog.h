/*
Copyright 2012-2013  Francesco Cecconi <francesco.cecconi@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SELECTPROFILEDIALOG_H
#define SELECTPROFILEDIALOG_H

#include <QDialog>
#include <QComboBox>

#include "ui_selectprofiledialog.h"

class MainWindow;

class SelectProfileDialog : public QDialog, private Ui::selectProfileDialog
{
    Q_OBJECT

public:
    SelectProfileDialog(MainWindow* ui);
    ~SelectProfileDialog();

private:
    void loadComboValues();

    MainWindow* m_ui;

private slots:
    void closeDialog();

};

#endif // SELECTPROFILEDIALOG_H
