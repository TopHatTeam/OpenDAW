# How to install gnustep

first you install **tools-make** from github but here are some dependencis you are going to need to install **tools-make**

### Debian based distros
```
sudo apt-get install texinfo texlive
```

now to build

```
cd /path/to/tools-make
./configure
make 
sudo make install
```

if it keeps saying **gmake install** when you type make then do this

```
sudo gmake install 
```

if you want to install the documentation then do this 
```
cd Documentation
make 
```

