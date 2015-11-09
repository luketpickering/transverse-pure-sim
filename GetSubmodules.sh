#!/bin/sh
git submodule init
git submodule update
git submodule foreach --recursive git submodule init
git submodule foreach --recursive git submodule update
git config status.submodulesummary 1
