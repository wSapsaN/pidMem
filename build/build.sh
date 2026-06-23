#!/bin/env bash

NAMEAPP="app";
SOURCE_FOLDER="../source";
SOURCE_FILE="main.c deepMem.c";
HEADERS_PATH="../include";
FLAGS="-g -Wall -I${HEADERS_PATH} -o ${NAMEAPP}";

[[ -n $(ls "${SOURCE_FOLDER}" 2> /dev/null) ]] && {
  printf "Build...\n";
  
  FULL_SOURCE_PATH="";
  for file_name in ${SOURCE_FILE}
  do
    FULL_SOURCE_PATH="${FULL_SOURCE_PATH} ${SOURCE_FOLDER}/${file_name}";
  done
  
  # printf "%s\n" "${FULL_SOURCE_PATH}";

  BUILD="gcc${FULL_SOURCE_PATH} ${FLAGS}"
  printf "\033[34m%s\033[0m\n" "${BUILD}";
  
  eval "${BUILD}";

  printf "\033[32;40mThe assembly is ready. Your file \"${NAMEAPP}\".\033[0m\n";
} || {
  printf "\033[31mSource file not found.\nRun this script in \"build\" folder please.\033[0m\n";
}
