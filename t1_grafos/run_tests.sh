#!/bin/bash

# Directory containing the instances
INSTANCE_DIR="instancias_t2"

# Check if the directory exists
if [ ! -d "$INSTANCE_DIR" ]; then
  echo "Directory $INSTANCE_DIR not found!"
  exit 1
fi

# Loop through all .txt files in the directory
for file in "$INSTANCE_DIR"/*.txt; do
  echo "Running heuristics on: $file"
  # 3 -> Go to Heuristics Menu
  # 4 -> Run all heuristics
  # 0 -> Go back to Main Menu
  # 0 -> Exit
  printf "3\n4\n0\n0\n" | ./execGrupo14 "$file"
  echo "---------------------------------"
done
