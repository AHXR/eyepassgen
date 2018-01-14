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
#include "ui_window.h"
#include "window.h"
#include "pool.h"
#include "time.h"
#include <string>
#include <Windows.h>

#pragma comment(lib, "user32.lib")

using namespace std;

unsigned short us_last_pos = 1;
unsigned short getIndexOfPool( size_t len );

window::window(QWidget *parent) : QMainWindow(parent), ui(new Ui::window) {
    ui->setupUi(this);

    QStringList qstr_list;
    char c_res[ 30 ];
    char c_level[ 5 ];

    for( unsigned short us = 5; us <= 50; us ++ ) {
        if( us >= 5 && us <= 10 )
            strcpy( c_level, "Weak");
        else if( us >= 11 && us <= 30 )
            strcpy( c_level, "Good");
        else if( us >= 31 && us <= 50 )
            strcpy( c_level, "Extreme");

        sprintf( c_res, "%i Characters (%s)", us, c_level );
        qstr_list += (QStringList() << c_res);
    }

    ui->cmbLength->addItems( qstr_list );
    srand(time(NULL));
}

window::~window() {
    delete ui;
}

void window::on_horizontalSlider_sliderMoved(int position) {
    updateGenerateAmount( ( unsigned short ) position );
}

void window::on_horizontalSlider_valueChanged(int value) {
    updateGenerateAmount( ( unsigned short ) value );
}

void window::updateGenerateAmount( unsigned short amount ) {
    char c_gen[ 30 ];

    if( amount > 1 )
        sprintf( c_gen, "Generate %i Passwords", amount );
    else
        strcpy( c_gen, "Generate Password" );

    us_last_pos = amount;
    ui->btnGenerate->setText(c_gen);
}

void window::on_lstPasswords_itemDoubleClicked(QListWidgetItem *item) {
    HWND win_handle;
    HGLOBAL hGlobal;
    char cq_password[ 50 ];
    string s_password;

    strcpy( cq_password, item->text().toLatin1().data() );
    s_password = cq_password;

    QMessageBox::StandardButton qAnswer = QMessageBox::question( this, "eyepassgen", "Would you like to copy this password to your clipboard?", QMessageBox::Yes | QMessageBox::No );

    if( qAnswer == QMessageBox::Yes)
    {
        win_handle = GetDesktopWindow();
        OpenClipboard( win_handle );
        EmptyClipboard();

        hGlobal = GlobalAlloc( GMEM_MOVEABLE, s_password.size() + 1 );
        if( !hGlobal )
            CloseClipboard();
        else {
            memcpy(GlobalLock(hGlobal), cq_password, s_password.size()+1);
            GlobalUnlock(hGlobal);
            SetClipboardData(CF_TEXT,hGlobal);
            CloseClipboard();
            GlobalFree(hGlobal);
        }
    }
}

void window::on_btnGenerate_released() {
    ui->lstPasswords->clear();

    char c_tmp_length[ 30 ];
    string s_length;
    unsigned short us_length;

    strcpy( c_tmp_length, ui->cmbLength->itemText( ui->cmbLength->currentIndex()).toLatin1().data() );

    s_length = c_tmp_length;
    s_length = s_length.substr( 0, s_length.find_first_of(' '));
    us_length = atoi( s_length.c_str() );

    for( unsigned short us = 0; us < us_last_pos; us ++ ) {
        char c_password_pool[ 100 ];
        char c_letter_pool[ 60 ];
        char c_pw[ 50 ];

        strcpy( c_pw, "" );
        strcpy( c_password_pool, "" );
        strcpy( c_letter_pool, "" );

        if( ui->chkNumbers->isChecked() )
            strcat( c_password_pool, p_numbers );

        if( ui->chkLowercase->isChecked() ) {
            strcat( c_password_pool, p_lowercase );
            strcat( c_letter_pool, p_lowercase );
        }
        if( ui->chkUppercase->isChecked() ) {
            strcat( c_password_pool, p_uppercase );
            strcat( c_letter_pool, p_uppercase );
        }

        if( ui->chkSymbols->isChecked() )
            strcat( c_password_pool, p_symbols );

        unsigned short i_index, i_last_index;
        char c_tmp_char[ 1 ];

        for( unsigned short i = 1; i <= us_length; i ++ ) {
            i_index = getIndexOfPool( strlen(c_password_pool) );

            if( i == 1 && ui->chkStarting->isChecked() ) {
                if( strlen( c_letter_pool ) > 0 ) {
                    i_index = getIndexOfPool( strlen(c_letter_pool) );
                    sprintf(c_tmp_char, "%c",  c_letter_pool[i_index]);
                }
            }
            else if( i != 1 ) {
                if( !isSymbol( i_last_index ) ) // Numbers and characters. Symbols are always unique
                    while( i_index == i_last_index + 1 )
                     i_index = getIndexOfPool( strlen(c_password_pool) );

                if( ui->chkUCharacters->isChecked() ) {
                    if( strlen( c_letter_pool ) > 0 )
                        for( unsigned short x = 0; x < strlen( c_pw ); x++ )
                            while( c_pw[ x ] == c_password_pool[ i_index ] )
                                i_index = getIndexOfPool( strlen(c_password_pool) );
                }

                sprintf(c_tmp_char, "%c",  c_password_pool[i_index]);
            }
            else
                sprintf(c_tmp_char, "%c",  c_password_pool[i_index]);

            i_last_index = i_index;
            strcat( c_pw, c_tmp_char );
        }

        ui->lstPasswords->addItem( c_pw );
    }
}

unsigned short getIndexOfPool( size_t len ) {
    return rand() % (unsigned short) len;
}
