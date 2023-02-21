#!/bin/bash

read -p "continue : (y/n)" yn
case $yn in
	[nN] ) exit;
esac
git add . > /dev/null
git commit -m "$1" > /dev/null
git push