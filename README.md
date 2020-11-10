# Evitar erro com o uso de video
xhost +local:docker

### Buildando o docker
## Always use sudo to run docker
# sudo docker build . -f Dockerfile -t nomedodocker
sudo docker build . -f Rodetas -t runrodetas.sh

# Navegando no docker
sudo docker run -it runrodetas.sh /bin/bash

# Buildando projeto
sudo ./build_test.sh

# Buildando VSS-Core manualmente
cd VSS-Core
sudo ./configure.sh
cd ..

# Buildando as biblotecas restantes
cd build
sudo cmake ..
sudo make -j4

# Executando o codigo Rodetas
sudo ./SDK-Rodetas [-c] [--colors]
