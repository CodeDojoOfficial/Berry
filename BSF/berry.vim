" Vim syntax file
" Language: Berry
" Maintainer: Adrian Gjerstad
" Latest Revision: 6 September 2018
" 
" MIT License
" 
" Copyright 2018 CodeDojo
" 
" Permissiossion is hereby granted, free of charge, to any person obtaining a copy
" of this software and associated documentation files (the "Software"), to deal
" in the Software without restriction, including without limitation the rights
" to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
" copies of the Software, and to permit persons to whom the Software is
" furnished to do so, subject to the following conditions:
" 
" The above copyright notice and this permission notice shall be included in all
" copies or substantial portions of the Software.

" THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
" IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
" FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
" AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
" LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
" OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
" SOFTWARE. 
" 
" To implement this Vim syntax file, move this into ${VIMHOME}/syntax/berry.vim,
" and put the following code into ${VIMHOME}/ftdetect/berry.vim:
"   
"   au BufRead,BufNewFile *.bry setfiletype berry
"   
" You should be good to go! Launch up Vim and edit a Berry source file, and it will
" highlight as is defined below!

if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

" Comments that contain TODO FIXME XXX or NOTE
syn keyword berryTodo       contained TODO FIXME XXX NOTE
syn cluster berryCommentGrp contains=berryTodo

" Increment/Decrement
syn match berryValue   /+/
syn match berryValue   /-/

" Switch cells
syn match berryFocus   />/
syn match berryFocus   /</

" IO
syn match berryOutput  /\./
syn match berryInput   /,/

" Loops
syn match berryLoop    /\[/
syn match berryLoop    /\]/

" Comments
syn match berryComment /[^+-><\.,\[\]]/ contains=berryCommentGrp
syn match berryComment /\d/             contains=berryCommentGrp
syn match berryComment /[=\\;/:]/       contains=berryCommentGrp

let b:current_syntax = "berry"

hi def link berryValue   Number
hi def link berryFocus   Statement
hi def link berryOutput  Type
hi def link berryInput   PreProc

hi def      berryLoop    term=bold cterm=bold ctermfg=Yellow gui=bold guifg=Yellow

hi def link berryComment Comment
hi def link berryTodo    Todo

