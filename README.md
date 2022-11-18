# Sparks

This repository contains the source code of our project for the ING1 course "Projet C" at CY Tech.

Authors : Achraf Assakan, Charles-Meldhine Madi Mnemoi, Dean Bah, Marwa Tourabi, Sithursha Sivathevan, Youssef Saidi

# Setup the development environment

## On Linux

* Install dependencies : 

```bash
sudo apt update && sudo apt upgrade
sudo apt-get install build-essential -y
```

* Setup a GitHub SSH key :
    
    * [Generate it](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
    * [Add it to your GitHub account](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)

* Clone the repository : 

```bash
git clone git@github.com:YoussefSA2/Sparks.git
cd Sparks
```

## On Windows

* Install [chocolatey](https://chocolatey.org/install) : 

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

* Install build tools : 

```powershell
choco install git mingw make -y
```

* Setup a GitHub SSH key :
    
    * [Generate it](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
    * [Add it to your GitHub account](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)

* Clone the repository : 

Open Git Bash and run the following commands : 

```bash
git clone git@github.com:YoussefSA2/Sparks.git
cd Sparks
```

# Launch the game

```bash
make run-game
```

# Launch the tests

```bash
make run-tests
```
