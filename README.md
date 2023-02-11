# INF3995 - Projet de conception d'un syst. informatique
Dans le cadre du projet intégrateur INF3995. Nous avons construit Dronu, un système aérien d'exploration. Le système est composé de deux parties principales:<br>
**Partie embarqué:** des drones physiques Crazyflie 2.0 programmés à effectuer des opérations & des simulations et envoyer des données à un station au sol qui leur donne des instructions à effectuer.z <br>
**Station au sol:** ordinateur avec une interface Web qui communique avec les drones à travers un canal de communication à 2.4 GHz. 

## Démarrer le projet

Pour lancer le projet : `make start`

## Demo:
Prochainement...

## Cas d'utilisation:
À partir de cette application, l'utilisateur peut lancer des drones en mission, les arreter, les renvoyer à la base, les voir dans une carte avec une fréquence de 1Hz. Les drones ont la possibilité de communiquer entre eux avec le protocole 'Peer to Peer'...

## Préparation de l'installation (Débogage):
Ce projet assume que vous avez déjà `Node ^14.15.0` & `npm ^6.11.0` & `Docker` & `Docker Compose` & `Makefile` & `Flask`. Si vous ne l'avez pas, vous pouvez exécuter les commandes dans le tableau ci-dessous:<br>
Premièrement, clonez le projet : `git clone https://gitlab.com/polytechnique-montr-al/inf3995/20223/equipe-106/INF3995-106.git`.

| Commandes        | Sortie
|-----------------|-------------------------------------------------------------------|
| `npm install -g @angular/cli` | Installer Angular CLI |
| `curl -fsSL https://deb.nodesource.com/setup_14.x \| sudo -E bash -` <br> `sudo apt-get install -y nodejs` | Installer une version 14.x NodeJs. | 
| `sudo npm install npm -g`     | Installer la derniere version de Npm. |
| `sudo apt-get install make`     | Installer Makefile. |
| Installation de Docker | Suivre les instructions de ce lien :https://docs.docker.com/engine/install/ubuntu/ |
| `sudo apt install docker-compose` | Installer Docker Compose |
| `sudo groupadd docker`<br/> `sudo usermod -aG docker $(USERNAME)` <br>`newgrp docker` | Donner les permissions à Docker pour l'utiliser sans ajouter `sudo` au début de la commande. Remplacez $(USERNAME) par votre nom d'utilisateur. |
| `sudo apt install python3-pip` | Installer la commande Python Pip.  |
| `sudo cd server/src && sudo apt install python3-flask` | Installer Flask. |
| `sudo pip install -U flask-cors` | Installer les requis de python. Pour installer pytest, executez cette commande en remplaçant `flask-cors` par `pytest`. |

## Commandes de compilation (Débogage):
Maintenant vous êtes prêt à construire le projet sans problèmes, voici le guide de commandes de construction du projet:
| Commands        | Sortie
|-----------------|-------------------------------------------------------------------|
| `make setup` | Installer Npm dans le côté client et installer l'environnement virtuelle du serveur. |
| `make start-client-local`    | Construire localement le côté client du projet. |
| `make start-server-local`      | Construire localement le côté serveur du projet. |
| `make build-client`      | Construire l'image du côté client du projet sur Docker. |
| `make build-server`      | Construire l'image du côté serveur du projet sur Docker.  |
| `make start`      | Lance le conteneur du côté client et du côté serveur du projet en utilisant Docker Compose.  |
| `make down`      | Arréter les conteneurs lancer par `make start`. |

## Convention et style de programmation

# C++

Pour C++, il faut suivre la convention de google (https://google.github.io/styleguide/cppguide.html). Pour l'indentation, il faut utiliser deux espaces et non des tabs. Pour les commentaires dans le code, il vaut mieux utiliser // et non /* */. Lors de la définition d'une variable et d'une fonction, il faut utiliser snake_case. Pour définir une classe, une struct ou un enum, il faut utiliser PascalCase.

# Python

Pour Python, il faut suivre la convention de google (https://google.github.io/styleguide/pyguide.html). Pour la définition des variables et des fonctions, il faut utiliser snake_case. Pour la définition des classes, il faut utiliser PascalCase.

# TypeScript

Pour TypeScript, il faut suivre la convention de google (https://google.github.io/styleguide/tsguide.html).

# Tests serveurs

Aller dans le repertoire server/src/test
Lancer les tests avec la commande $./test.sh
