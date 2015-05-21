#! /bin/bash

echo "Runnng unit tests..."

for ex in ./test/*_test; do
    echo "Running $ex..."
    ./$ex
done

echo "All tests completed"
