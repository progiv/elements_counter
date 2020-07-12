## XML Elements counter
Counts number of Elements in XML documents list.

### Usage:
```
elements_counter <list of URLs leading to xml documents separated with space>
```

### Build
Depends on libcurl-dev(libcurl4-openssl-dev), libtbb-dev packages
```bash
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
``` 
