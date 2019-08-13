/*
    Oneiric, a small kernel based on how dreams work
    Copyright (C) 2019  Mesabloo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

.section .rodata
    .global err_code1
    .global err_code2
    .global err_code4
    .global err_codeU

    err_code1: .asciz "Panic! Internal error occured: code 0b00000001 - Kernel exited unexpectedly. "
    err_code2: .asciz "Panic! Internal error occured: code 0b00000010 - No multiboot data available. "
    err_code4: .asciz "Panic! Internal error occured: code 0b00000100 - Incorrect multiboot data. "
    err_codeU: .asciz "Panic! Internal error occured: unknown code. "
