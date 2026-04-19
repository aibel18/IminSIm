#!/bin/bash

# The formatting
Format() {
  local TARGET_PATH=${1:-.}

  if [ -f "$TARGET_PATH" ]; then
    clang-format -i "$TARGET_PATH"
    echo "Formatted file: $TARGET_PATH"
  else
    find "$TARGET_PATH" \
      \( -path "*/build" -o -path "*/sdk" -o -path "*/render/GL" -o -path "*/.git" \) -prune \
      -o -regex ".*\.\(cpp\|hpp\|cc\|cxx\|h\|hh\)" -exec clang-format -i {} +
    echo "Finished formatting directory: $TARGET_PATH"
  fi
}

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format is not installed."
    exit 1
fi

# Run the logic with the provided argument
Format "$1"

