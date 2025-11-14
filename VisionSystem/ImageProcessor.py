#!/usr/bin/env python3
import subprocess
import time


# Path to the script you want to run
script_to_run = "test.py"

# Start the timer
start_time = time.time()

#print(f"Starting script '{script_to_run}'...")

try:
    # Run the script as a subprocess
    result = subprocess.run(
        ["python3", script_to_run],
        capture_output=True,  # capture stdout/stderr
        text=True             # return outputs as strings
    )

    # Print the outputs of the script
#    print("=== Script Output ===")
#    print(result.stdout)
#    if result.stderr:
#        print("=== Script Errors ===")
#        print(result.stderr)

except Exception as e:
    print(f"Error running script: {e}")

# Stop the timer
end_time = time.time()
elapsed_time = end_time - start_time

print(f"\nScript '{script_to_run}' finished in {elapsed_time:.3f} seconds.")
