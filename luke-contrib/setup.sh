#!/bin/sh

if ! echo "${BASH_SOURCE}" | grep --silent "/"; then
  LCDIR=$(readlink -f $PWD)
else
  LCDIR=$(readlink -f ${BASH_SOURCE%/*})
fi

DIRSTOADD="${LCDIR}/generators/neut ${LCDIR}/generators/GiBUU ${LCDIR}/plotting ${LCDIR}/transverse-variable-tree-generation/all"

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
