#!/bin/sh

while true; do
    output=$(/tmp/lidor/a.out)  # Replace with your executable path
    case "$output" in
        *_*) echo "$output"; break ;;
    esac
done