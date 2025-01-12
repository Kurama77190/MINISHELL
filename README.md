<div align="center">
  <img height="450" src="https://raw.githubusercontent.com/Kurama77190/MINISHELL/refs/heads/main/img/minishell.png"  />
</div>

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
