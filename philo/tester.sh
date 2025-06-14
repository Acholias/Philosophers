#!/bin/bash

TIMEOUT_DURATION=10

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
RESET="\033[0m"

TEMP_LOG=$(mktemp)
RESULTS_LOG=$(mktemp)

handle_sigint(){
    trap '' SIGTERM
    echo -e "\n${RED}Tester interrompu par l'utilisateur${RESET}"
    rm -f "$TEMP_LOG" "$RESULTS_LOG"
    kill 0
    exit
}

trap handle_sigint SIGINT

declare -a TESTS=(
    "2 410 200 200"
    "4 410 200 200"
    "5 800 200 200"
    "200 610 200 200"
    "5 800 200 200 7"
    "10 210 120 120"
    "200 130 60 60"
)

declare -a RUNS=(
    3
    5
    5
    5
    3
    5
    5
)

if [ $# -eq 0 ]; then
    echo -e "${CYAN}Aucun argument fourni, lancement des tests prédéfinis.${RESET}"
    NB_TESTS=${#TESTS[@]}
    for ((i=0; i<NB_TESTS; i++)); do
        PHILO_ARGS="${TESTS[$i]}"
        RUN_COUNT="${RUNS[$i]}"
        echo -e "${YELLOW}Test $((i+1))/$NB_TESTS : ./philo $PHILO_ARGS ($RUN_COUNT runs)${RESET}"
        > "$RESULTS_LOG"
        for ((index=1; index<=RUN_COUNT; index++)); do
            timeout $TIMEOUT_DURATION ./philo $PHILO_ARGS > "$TEMP_LOG" 2>&1
            if grep -q "died" "$TEMP_LOG"; then
                PHILO_RESULT="${RED}KO${RESET}"
            else
                PHILO_RESULT="${GREEN}OK${RESET}"
            fi
            if grep -q "Possible data race" "$TEMP_LOG"; then
                HELGRIND_RESULT="${RED}KO${RESET}"
            else
                HELGRIND_RESULT="${GREEN}OK${RESET}"
            fi
            if [[ "$PHILO_RESULT" == *OK* && "$HELGRIND_RESULT" == *OK* ]]; then
                echo "OK" >> "$RESULTS_LOG"
            else
                echo "KO" >> "$RESULTS_LOG"
            fi
            printf "  Run $index : [philo: $PHILO_RESULT] [helgrind: $HELGRIND_RESULT]\n"
        done
        OK_COUNT=$(grep -c "OK" "$RESULTS_LOG")
        KO_COUNT=$(grep -c "KO" "$RESULTS_LOG")
        if [ "$KO_COUNT" -eq 0 ]; then
            echo -e "${GREEN}Résultat global : OK ($OK_COUNT/$RUN_COUNT)${RESET}\n"
        else
            echo -e "${RED}Résultat global : KO ($KO_COUNT/$RUN_COUNT)${RESET}\n"
        fi
    done
    rm -f "$TEMP_LOG" "$RESULTS_LOG"
    exit 0
fi

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
    echo -e "${RED}Checker arguments not set !\n"
    echo -e "Usage: $0 <philo_arguments> [runs]"
    echo -e "Example: $0 \"4 410 200 200\" 10${RESET}"
    exit 1
else
    if [[ $1 != *" "* ]]; then
        echo -e "${RED}Erreur : Les arguments du projet doivent être entre guillemets et contenir plusieurs valeurs !"
        echo -e "Exemple: $0 \"4 410 200 200\".${RESET}"
        exit 1
    fi
    PHILO_ARGS=$1
    if [ $# -ge 2 ]; then
        if [[ $2 =~ ^[0-9]+$ ]]; then
            RUNS=$2
            if [ "$RUNS" -gt 50 ]; then
                echo -e "${RED}Erreur : Le nombre de runs ne peut pas dépasser 1000.${RESET}"
                exit 1
            fi
        else
            echo -e "${RED}Erreur : Le deuxième argument (nombre de runs) doit être un entier positif.${RESET}"
            exit 1
        fi
    else
        RUNS=5
    fi
fi

echo -e "${YELLOW}Testing your current project ⏳⚙️:\n${RESET}"
> "$RESULTS_LOG"
for ((index=1; index<=RUNS; index++)); do
    timeout $TIMEOUT_DURATION ./philo $PHILO_ARGS > "$TEMP_LOG" 2>&1
    if grep -q "died" "$TEMP_LOG"; then
        PHILO_RESULT="${RED}KO${RESET}"
    else
        PHILO_RESULT="${GREEN}OK${RESET}"
    fi
    if grep -q "Possible data race" "$TEMP_LOG"; then
        HELGRIND_RESULT="${RED}KO${RESET}"
    else
        HELGRIND_RESULT="${GREEN}OK${RESET}"
    fi
    if [[ "$PHILO_RESULT" == *OK* && "$HELGRIND_RESULT" == *OK* ]]; then
        echo "OK" >> "$RESULTS_LOG"
    else
        echo "KO" >> "$RESULTS_LOG"
    fi
    printf "Testing : [philo: $PHILO_RESULT] [helgrind: $HELGRIND_RESULT]\n"
done

OK_COUNT=$(grep -c "OK" "$RESULTS_LOG")
KO_COUNT=$(grep -c "KO" "$RESULTS_LOG")

echo -e "\n${GREEN}✔ OK: ${OK_COUNT}${RESET}"
echo -e "${RED}✘ KO: ${KO_COUNT}${RESET}"

rm -f "$TEMP_LOG" "$RESULTS_LOG"