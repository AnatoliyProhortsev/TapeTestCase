# Yadro Test-case: tape sorter

## Dependencies
- GoogleTest

## 1 step - build and install GTest framework
#### When you in /downloads/ or any else dir
```bash
git clone https://github.com/google/googletest.git
cd googletest && mkdir build && cd build && cmake .. && sudo make && sudo make install
```
## 2 step - build TapeSorter
#### Download project from git:
```bash
git clone https://github.com/AnatoliyProhortsev/TapeTestCase.git && cd TapeTestCase
```
#### Build sorter:
```bash
sudo make build
```
#### Build tests:
```bash
sudo make tests
```
#### Clean project dir:
```bash
sudo make clean
```
## Usage
#### Run builded TapeSorter tests:
```bash
cd bin && ./TapeSorterTest
```
#### Run sorter with command-line parameters
```bash
cd bin
./TapeSorter [config path] [input tape file] [out tape file]
```
## Where useful files contains (relative to executable):
#### Config files: ../cfg
#### Input tapes: ../tapes
