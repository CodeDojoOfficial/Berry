#!/bin/bash

echo "Checking for certain environment conditions... (2)"

echo "Checking for an internet connection..."

wget -q --spider https://codedojoofficial.github.io 2>/dev/null

if [[ $? -eq 0 ]]; then
  echo "Internet connection found. Continuing checks... (1/2)"
else
  echo "You are offline. Try connecting to a stable internet connection before installing."
  return 1
fi

sudo -v 2>/dev/null

if [[ $? -eq 0 ]]; then
  echo "Super User access has been confirmed. (2/2)"
else
  echo "You do not have sudo access in this profile. Try running sudo source ${BASH_SOURCE} instead."
  return 1
fi

echo "Installing Berry v1.0.0_0 ..."
echo "Creating git repository to retrieve details..."

git clone https://github.com/CodeDojoOfficial/Berry.git

echo "Unpackaging..."

mkdir -p /usr/berry/bin/BDK

cd Berry/BDK/
mv bin/compiler /usr/berry/bin/BDK/compiler
mv berry.sh /usr/berry/bin/BDK/berry.sh

echo "Unpackaged. Cleaning up..."

cd ../../../
rm -r Berry

echo "" >> ${HOME}/.bashrc
echo "# Berry imports v1.0.0_0" >> ${HOME}/.bashrc
echo "export BERRY_HOME=\"/usr/berry/bin/" >> ${HOME}/.bashrc
echo "source \${BERRY_HOME}/BDK/berry.sh # Initialize the berry command" >> ${HOME}/.bashrc

echo "Installed. Let your Berry adventures begin!"

source ${HOME}/.bashrc
