## Highlighting and Removing Trailing Whitespaces.

Add the below content to the end of file /etc/vim/vimrc and Save it.

Now you can see the trailing while spaces in red colour, and if you do  :w for any other file, white spaces will be removed.
```
" To highlight trailing whitespaces
highlight RedundantSpaces ctermbg=red guibg=red
match RedundantSpaces /\s\+$/

" To remove trailing whitespaces
autocmd BufWritePre * :%s/\s\+$//e
```
------------------------------------------------------------------------------------------------
