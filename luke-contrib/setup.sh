#!/bin/sh

DIRSTOADD="./generators/neut/neut2rootracker ./generators/GiBUU ./plotting ./transverse-variable-tree-generation/all"

CPWD=$PWD

for DIR in $DIRSTOADD; do
  echo "Moving to $DIR"
  cd "$DIR"
  if [ -e "setup.sh" ]; then
    . ./setup.sh
    echo "Sourced ${DIR}/setup.sh"
  fi
  cd "$CPWD"
done
