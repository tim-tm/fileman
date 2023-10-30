[![Ubuntu build](https://github.com/tim-tm/fileman/actions/workflows/makefile.yml/badge.svg)](https://github.com/tim-tm/fileman/actions/workflows/makefile.yml)

# fileman

### This project is by far not production ready and for now only made for educational purposes.
### Windows is not supported for now.

fileman is a really simple filemanager, inside of the cli.

## Dependencies
- libc

## Setting up

Cloning the repo
```sh
git clone https://github.com/tim-tm/fileman.git && cd fileman
```

Building
```sh
make setup && make
```

Installing (optionally)
```sh
make install
```

## Keys

arrow-up
: Move the cursor up

arrow-down
: Move the cursor down

'q'
: Quit fileman

'r'
: Rename the selected file

'd'
: Delete the selected file

':'
: Enter the selected directory or submit the new filename

'o'
: Open the selected file or directory in neovim
