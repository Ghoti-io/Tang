" Auto-reload changed files.
set autoread

" Toggle between absolute and relative numbering automatically
" set number relativenumber
augroup numbertoggle
  autocmd!
  autocmd BufEnter,FocusGained,InsertLeave * set relativenumber
  autocmd BufLeave,FocusLost,InsertEnter   * set norelativenumber
augroup END

set bg=dark
set tabstop=2
set shiftwidth=2
set expandtab
set nu

" To list the available color schemes, run:
" ll /usr/share/vim/vim*/colors*
color slate

"set mouse=a

filetype on
filetype indent on
filetype plugin on

if has("syntax")
  syntax on
endif

" Stolen from: https://superuser.com/questions/632657/how-to-setup-vim-to-edit-both-makefile-and-normal-code-files-with-two-different
" Makes tabs spaces, unless it should be tabs (e.g., Makefiles)

augroup FileTypeTabs

  autocmd FileType mail set formatoptions+=t textwidth=72 " enable wrapping in mail
  autocmd FileType human set formatoptions-=t textwidth=0 " disable wrapping in txt

  " for C-like  programming where comments have explicit end
  " characters, if starting a new line in the middle of a comment automatically
  " insert the comment leader characters:
  autocmd FileType c,cpp,java set formatoptions+=ro
  autocmd FileType c set omnifunc=ccomplete#Complete

  " fixed indentation should be OK for XML and CSS. People have fast internet
  " anyway. Indentation set to 2.
  autocmd FileType html,xhtml,css,xml,xslt set shiftwidth=2 softtabstop=2

  " two space indentation for some files
  autocmd FileType vim,lua,nginx set shiftwidth=2 softtabstop=2

  " for CSS, also have things in braces indented:
  autocmd FileType css set omnifunc=csscomplete#CompleteCSS

  " add completion for xHTML
  autocmd FileType xhtml,html set omnifunc=htmlcomplete#CompleteTags

  " add completion for XML
  autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags

  " in makefiles, don't expand tabs to spaces, since actual tab characters are
  " needed, and have indentation at 8 chars to be sure that all indents are tabs
  " (despite the mappings later):
  autocmd FileType make set noexpandtab shiftwidth=8 softtabstop=0

  " ensure normal tabs in assembly files
  " and set to NASM syntax highlighting
  autocmd FileType asm set noexpandtab shiftwidth=8 softtabstop=0 syntax=nasm

augroup END



" https://codeyarns.com/tech/2014-09-02-how-to-fold-code-in-vim.html
" Code folding

" Keep all folds open when a file is opened
set foldmethod=syntax
" set foldmethod=indent

" Folding is enabled by default, but can be changed.
" set foldenable
" set nofoldenable

augroup OpenAllFoldsOnFileOpen
    autocmd!
    autocmd BufRead * normal zR
augroup END

" za: Toggle code folding.
" zR: Open all folds.
" zM: Close all folds.
" zo: Open current fold.
" zc: Close current fold.


