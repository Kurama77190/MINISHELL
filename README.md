<div align="center">
  <img height="450" src="https://raw.githubusercontent.com/Kurama77190/MINISHELL/refs/heads/main/img/minishell.png"  />
</div>

## MINISHELL
Bienvenue sur **Minishell**, un projet passionnant réalisé dans le cadre de l'école 42. Minishell est un interpréteur de commandes minimaliste qui réplique certaines fonctionnalités des shells Unix comme `bash`.

## 🎯 Objectif

Créer un shell fonctionnel qui peut :
- Exécuter des commandes Unix simples.
- Gérer les redirections (`<`, `>`, `>>`) et les pipes (`|`).
- Implémenter des commandes "built-in" comme `cd`, `echo`, `pwd`, `export`, `unset`, `env`, et `exit`.
- Respecter les signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) pour imiter le comportement de `bash`.

## 🚀 Fonctionnalités principales

- **Exécution de commandes** :
  - Gère les chemins absolus ou relatifs.
  - Supporte les commandes avec des arguments.
- **Redirections et pipes** :
  - Redirection d'entrée et de sortie (`<`, `>`, `>>`).
  - Piping entre plusieurs commandes (`|`).
- **Commandes built-in** :
  - `cd` : Change de répertoire.
  - `echo` : Affiche une ligne de texte.
  - `pwd` : Affiche le répertoire courant.
  - `export` : Ajoute ou modifie des variables d'environnement.
  - `unset` : Supprime des variables d'environnement.
  - `env` : Affiche toutes les variables d'environnement.
  - `exit` : Quitte le shell.
- **Gestion des signaux** :
  - `Ctrl+C` : Arrête une commande en cours d'exécution.
  - `Ctrl+D` : Quitte le shell si aucune commande n'est en cours.
  - `Ctrl+\` : Ignoré.

## ⚙️ Installation et utilisation

### Prérequis

- Un système Unix (Linux ou macOS).
- `gcc` ou tout autre compilateur C compatible.

### Installation

Clone ce dépôt et compilez le projet avec `make` :
```bash
git clone https://github.com/<ton_utilisateur>/minishell.git
cd minishell
make
```

### Lancement

Lance le shell en exécutant :
```bash
./minishell
```

### Exemple d'utilisation

```bash
minishell$ echo "Hello, world!"
Hello, world!
minishell$ ls | grep minishell
minishell
minishell$ cd ..
minishell$ exit
```

## 🛠️ Structure du projet

- **src/** : Contient le code source principal.
- **includes/** : Contient les fichiers d'en-tête.
- **Makefile** : Automatisation de la compilation.

## 👫 Collaboration

Ce projet a été réalisé en collaboration avec **Ralph (MortalTrex)**. Son expertise technique et sa rigueur ont été précieuses pour mener ce projet à bien. Merci à Ralph pour son travail acharné et ses idées innovantes !

## 📚 Apprentissage

Durant ce projet, nous avons maîtrisé des concepts avancés comme :

- **Gestion des processus** :
  - Création et synchronisation de processus avec `fork`, `execve`, `waitpid`.
  - Communication entre processus via des pipes tout en évitant les fuites de descripteurs de fichiers.

- **Tokenisation et parsing** :
  - Analyse syntaxique des commandes utilisateur.
  - Gestion efficace des redirections et des pipes dans des structures organisées.

- **Implémentation des signaux** :
  - Gestion des signaux Unix pour une expérience utilisateur fluide et proche de `bash`.
  - Manipulation avancée de `readline` pour capturer et traiter les entrées utilisateur.

- **Mémoire et performance** :
  - Allocation dynamique et gestion de listes chaînées pour stocker les commandes et les arguments.
  - Identification et résolution des fuites mémoire avec des outils comme Valgrind.

- **Débogage et optimisation** :
  - Utilisation d'outils de diagnostic pour analyser les comportements des processus et des descripteurs de fichiers.
  - Adaptation du code pour gérer des cas limites et maximiser la stabilité.

## 📝 Licence

Ce projet est sous licence [MIT](https://opensource.org/licenses/MIT).

