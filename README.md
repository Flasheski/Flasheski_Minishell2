# 🐚 MINISHELL2 - FLASHESKI

## 🧭 DESCRIPTION DU PROJET

- L'objectif de ce projet est d'enrichir votre projet `minishell1` en y ajoutant des fonctionnalités avancées.
- Le programme doit désormais gérer les points-virgules (`;`), les pipes (`|`) et les quatre redirections (`>`, `<`, `>>`, `<<`).
- La gestion des priorités entre ces opérateurs est un élément clé de la réalisation.
- Comme pour la version précédente, le binaire doit se nommer `mysh`.

## 🗓️ DATES

📅 **Projet en cours - Mai 2026**

## 🛠️ Fonctionnalités attendues

- **Exécution de binaires** : Utilisation de votre `minishell1` fonctionnel pour lancer des programmes.
- **Semicolons (`;`)** : Permet d'enchaîner plusieurs commandes sur une seule ligne.
- **Pipes (`|`)** : Gestion de la communication entre processus.
- **Redirections** :
    - Sortie standard (`>`) et mode ajout (`>>`).
    - Entrée standard (`<`) et "double left redirection" (`<<`).

> [!NOTE]
> ⚠️ Les redirections de la sortie d'erreur (`2>`) ou les combinaisons complexes (`2>&1`) sont considérées comme des bonus.

## 🚀 UTILISATION

### - Lancement :
```bash
# Compilation via le Makefile (règles clean, fclean, re incluses)
make 
./mysh
```
### ⚙️ - Interactions :

#### 💻​ - Mode interactif :

**Vous pouvez utiliser n'importe quel prompt pour tester les commandes enchaînées :**

<img width="563" height="61" alt="image" src="https://github.com/user-attachments/assets/a7033c7c-1c19-47a1-9659-bd8df5de9d2d" />

<img width="727" height="422" alt="image" src="https://github.com/user-attachments/assets/00382edf-b366-4ff0-b853-d03ba77cd91a" />

#### 🖥️ - Mode non-interactif :

**Le shell doit traiter les commandes envoyées via un pipe :**

```bash
echo "mkdir test; cd test; ls | cat | wc -c > tutu; cat tutu" | ./mysh
```

> [!IMPORTANT]
> Les messages d'erreur doivent être écrits sur la sortie d'erreur (stderr). En cas d'erreur, le programme doit quitter avec le code 84 (0 sinon).

## 📜 RÈGLES ET CONTRAINTES :

* Langage : C.
* Groupe : 1 personne
* Fonctions autorisées : ```malloc```, ```free```, ```exit```, ```opendir```, ```readdir```, ```closedir```, ```getcwd```, ```chdir```, ```fork```, ```stat```, ```lstat```, ```fstat```, ```open```, ```close```, ```getline```, ```strtok```, ```strtok_r```, ```read```, ```write```, ```execve```, ```access```, ```isatty```, ```wait```, ```waitpid```, ```wait3```, ```wait4```, ```signal```, ```kill```, ```getpid```, ```strerror```, ```perror```, ```strsignal```, ```pipe```, ```dup```, ```dup2```.

## 📁 FICHIERS && STRUCTURE DU PROJET :

```bash

├── bonus
│   └── display_bonus.c
├── include
│   ├── my.h
│   └── shell.h
├── lib
│   ├── libmy.a
│   └── my/
├── Makefile
├── mysh
├── README.md
└── src
    ├── commands
    │   ├── cd_command.c
    │   ├── find_command.c
    │   ├── handle_command.c
    │   └── print_cd_path.c
    ├── envs
    │   ├── free_env.c
    │   ├── my_setenv.c
    │   ├── my_unsetenv.c
    │   └── put_env.c
    ├── exec
    │   └── exec.c
    ├── main.c
    ├── paths
    │   ├── check_paths.c
    │   ├── get_path.c
    │   └── process_lines.c
    ├── pipes
    │   ├── check_pipes.c
    │   └── handle_pipe.c
    ├── redirects
    │   └── handle_redirections.c
    ├── signals
    │   └── signals.c
    └── utils
        └── free_array.c
```

<img width="253" height="529" alt="image" src="https://github.com/user-attachments/assets/3fdc0ac5-063f-41bf-9c14-1e94e8a928b6" />

