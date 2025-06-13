#!/bin/bash

RUNS=50
TIMEOUT_DURATION=10

GREEN="\033[1;32m"
RED="\033[1;31m"
RESET="\033[0m"

TEMP_LOG=$(mktemp)
RESULTS_LOG=$(mktemp)

handle_sigint(){
    echo -e "\n${RED}Tester interrompu par l'utilisateur${RESET}"
    rm -f "$TEMP_LOG" "$RESULTS_LOG"
    kill 0
    exit
}

trap handle_sigint SIGINT

if [ $# -lt 1 ]; then
    echo "Usage: $0 <philo_arguments> [runs]"
    echo "Example: $0 \"4 410 200 200\" 10"
    exit 1
fi

PHILO_ARGS=$1

if [ $# -ge 2 ]; then
    if [[ $2 =~ ^[0-9]+$ ]]; then
        RUNS=$2
        if [ "$RUNS" -gt 1000 ]; then
            echo -e "${RED}Erreur : Le nombre de runs ne peut pas dépasser 1000.${RESET}"
            exit 1
        fi
    else
        echo -e "${RED}Erreur : Le deuxième argument (nombre de runs) doit être un entier positif.${RESET}"
        exit 1
    fi
fi

run_test() {
    local index=$1
    timeout $TIMEOUT_DURATION valgrind --tool=helgrind ./philo $PHILO_ARGS 2>&1 | grep -q "Possible data race"
    if [ $? -eq 0 ]; then
        echo "KO" >> "$RESULTS_LOG"
        printf "RUN %-3d: ${RED}✘ KO${RESET}\n" "$index"
    else
        echo "OK" >> "$RESULTS_LOG"
        printf "RUN %-3d: ${GREEN}✔ OK${RESET}\n" "$index"
    fi
}

for ((index=1; index<=RUNS; index++))
do
    run_test $index &
done

wait

OK_COUNT=$(grep -c "OK" "$RESULTS_LOG")
KO_COUNT=$(grep -c "KO" "$RESULTS_LOG")

echo -e "\n${GREEN}✔ OK: ${OK_COUNT}${RESET}"
echo -e "${RED}✘ KO: ${KO_COUNT}${RESET}"

rm -f "$TEMP_LOG" "$RESULTS_LOG"