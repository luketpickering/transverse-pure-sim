#!/bin/sh

if ! echo "${BASH_SOURCE}" | grep --silent "/"; then
  LCDIR=$(readlink -f $PWD)
else
  LCDIR=$(readlink -f ${BASH_SOURCE%/*})
fi

DIRSTOADD="${LCDIR}/generators/neut ${LCDIR}/plotting ${LCDIR}/transverse-variable-tree-generation"

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

unset DIRSTOADD
unset DIR
unset LCDIR
unset CPWD
