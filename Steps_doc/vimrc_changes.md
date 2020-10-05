Add the below content to the end of file `/etc/vim/vimrc` for all users or add this to `~/.vimrc` for particular user (if `~.vimrc` doesn't exist create it)

### Highlight serch
```
set hlsearch
```

### C file auto indent
```
set autoindent
set cindent
```

### Set tabs for required spaces
```
set tabstop=4
set shiftwidth=4
```

### Highlight trailing whitespace
```
highlight ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace /\s\+$/
```

### Remove trailing whitespece on file save
```
autocmd BufWritePre * %s/\s\+$//e
```
