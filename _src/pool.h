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
#ifndef POOL_H
#define POOL_H

char p_numbers[ 11 ] = "0123456789";
char p_lowercase[ 27 ] = "abcdefghijklmnopqrstuvwxyz";
char p_uppercase[ 27 ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char p_symbols[ 35 ] = "!\";#$%&'()*+,-./:;<=>?@[]^_`{|}~";

bool isSymbol( char c );

bool isSymbol( char c ) {
    for( unsigned short i = 0; i < strlen( p_symbols ); i ++ )
        if( p_symbols[ i ] == c )
            return true;

    return false;
}

#endif // POOL_H
