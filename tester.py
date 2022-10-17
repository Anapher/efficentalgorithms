import sys
from os import path
from subprocess import call, run

SCRIPT_NAME = "main.cpp"

test_case = sys.argv[1]

print(f"Test case {test_case}")


def read_file_in_testcase(filename):
    try:
        with open(path.join(test_case, filename), "r") as f:
            return f.read()
    except Exception as e:
        print(f"Error while reading {filename}")
        print(e)
        sys.exit(-1)


input = read_file_in_testcase("input.txt")
expected_output = read_file_in_testcase("output.txt")

print("Compile main.cpp...")
call(["g++", "-std=c++11", path.join(test_case, SCRIPT_NAME)])

print("Run application")
p = run(["./a.out"], input=input, capture_output=True, text=True)
print(p.stdout)
