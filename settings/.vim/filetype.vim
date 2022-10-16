" https://vi.stackexchange.com/a/5203
if exists("did_load_filetypes")
  finish
endif
augroup filetypedetect
  au! BufRead,BufNewFile *.y  setfiletype c
  au! BufRead,BufNewFile *.l  setfiletype c
augroup END

