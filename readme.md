# pass-gen a simple password generator in c
## dependence
- c99 compiler (tested on gcc)
- c99 libc (tested on glibc)
## how to build:
```shell
make
sudo make install
```
## how to use:
```
usage:
	pass-gen [options] [character-set]
option:
	-c --count <nunber>       How many password grnerate
	-l --length <nunber>      How long password should be
	-a --include-lower-case   Include all lower case letter [a-z]
	-A --include-upper-case   Include all upper case letter [A-Z]
	-s --include-special      Include special character like `!@#$.`
	-d --include-digits       Include all digits [0-9]
	-h --help                 Prints this mesage
```
