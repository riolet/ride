# Set gcc 4.8
echo 2 | sudo update-alternatives --config gcc

# Download the library
wget https://dl.dropboxusercontent.com/u/21877456/Library.tar.gz
tar -xvzf Library.tar.gz

# Install QScintilla
cd QScintilla/Qt4Qt5/
sudo qmake qscintilla.pro
sudo make
sudo make install
cd ../..

# Install Flex
sudo apt-get install flex

# Download and install bison
cd bison
./configure
sudo make
sudo make install
cd ..

# Trying to make project
cd ride-gui/
sudo qmake -project
sudo qmake
sudo make