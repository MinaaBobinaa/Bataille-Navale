
setup() {
  load 'bats/bats-support/load'
  load 'bats/bats-assert/load'
}

prog="bataille_navale"

@test "Quitter le jeu avec l'option 2" {
    run bash -c "echo '2' | ./$prog"
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "================================================" ]
    [ "${lines[1]}" = "Bienvenue dans le jeu de bataille navale !" ]
    [ "${lines[2]}" = "================================================" ]
    [ "${lines[3]}" = "Choisissez une option :" ]
    [ "${lines[4]}" = "1. Nouvelle partie" ]
    [ "${lines[5]}" = "2. Quitter" ]
    [ "${lines[6]}" = "Merci d'avoir joué. À bientôt!" ]
    assert_success
}

@test "Avec argument -S sans spécifier de fichier" {
    run ./$prog -S
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "Usage: ./bataille_navale [-S stats.txt]" ]
    assert_failure 1
}

@test "Choix invalide dans le menu" {
    run bash -c "printf '999\n2\n' | ./$prog"
    [ "${lines[0]}" = "================================================" ]
    [ "${lines[1]}" = "Bienvenue dans le jeu de bataille navale !" ]
    [ "${lines[2]}" = "================================================" ]
    [ "${lines[3]}" = "Choisissez une option :" ]
    [ "${lines[4]}" = "1. Nouvelle partie" ]
    [ "${lines[5]}" = "2. Quitter" ]
    [ "${lines[6]}" = "Choix non valide. Veuillez réessayer." ]
}


