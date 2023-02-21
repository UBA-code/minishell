#!/bin/bash

git add . > /dev/null
git commit -m "$1" > /dev/null
git push | > /dev/null