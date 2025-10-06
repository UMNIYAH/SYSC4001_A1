#!/bin/bash
INPUT_DIR="input_files"
OUTPUT_DIR="output_files"

mkdir -p $OUTPUT_DIR

VECTOR_TABLE="vector_table.txt"
DEVICE_TABLE="device_table.txt"

for file in $INPUT_DIR/*.txt; do
    filename=$(basename "$file" .txt)
    OUTPUT_FILE="$OUTPUT_DIR/execution_$filename.txt"
    echo "Running simulation for this file $file ..."
    ./bin/interrupts "$file" "$VECTOR_TABLE" "$DEVICE_TABLE"
    mv execution.txt "$OUTPUT_FILE"
done

echo "Simulations are completed: $OUTPUT_DIR."
