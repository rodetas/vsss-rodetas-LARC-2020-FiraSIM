# Evitar erro com o uso de video
xhost +local:docker

### Buildando o docker
## Always use sudo to run docker
# sudo docker build . -f Dockerfile -t nomedodocker
sudo docker build . -f Rodetas -t runrodetas.sh

# Navegando no docker
sudo docker run -it runrodetas.sh /bin/bash