#!/usr/bin/env python
"""
blackbox_test.py
Matthew Brooks, 2018
Tests mbvm using all of the programs in test_programs against their known
output.
"""
# For 2/3 compatible print()
from __future__ import print_function

import os
import subprocess
import sys


def test_program(program_name, expected_output):
    """
    Tests a program to make sure it outputs what we expect.

    :param program_name: the program to test
    :param expected_output: the expected output
    :return: 0 if passed 1 if failed
    """

    received_output = subprocess.check_output(
        [mbvm_exec, os.path.join(test_programs_dir, program_name)])

    # For 2/3 compatibility
    if not isinstance(received_output, str):
        received_output = received_output.decode("utf-8")

    print("testing '{}'... ".format(program_name), end="")

    if expected_output == received_output:
        print("passed")

        return 0
    else:
        print("failed! '{}' != '{}'".format(received_output, expected_output))

        return 1


def main():
    """
    The main()

    :return: None
    """

    failed_tests = 0
    failed_tests += test_program("hello_world", "hello world!\n")
    failed_tests += test_program("loop", "*")
    # TODO: Add more test cases here...

    if failed_tests:
        print("Errors: Failed '{}' tests!".format(str(failed_tests)))
    else:
        print("All tests passed!")


# Some global variables
root_project_dir = os.getcwd()
test_programs_dir = os.path.join(root_project_dir, "test_programs")
# TODO: Maybe try to get this to work via cygwin/mingw
# mbvm_windows_exec = os.path.join(root_project_dir, "exec", "mbvm.exe")
mbvm_unix_exec = os.path.join(root_project_dir, "exec", "mbvm")
mbvm_exec = None

# Find the right executable for Windows/*Nix
if os.name == "nt":
    sys.stderr.write("ERROR: Cannot test on Windows")
    sys.exit(1)
    # if os.path.isfile(mbvm_windows_exec):
    #     mbvm_exec = "c:\\cygwin64\\bin\\run.exe" + " " + mbvm_windows_exec
else:
    if os.path.isfile(mbvm_unix_exec):
        mbvm_exec = mbvm_unix_exec

if not mbvm_exec:
    sys.stderr.write("ERROR: Could not find the mbvm executable")
    sys.exit(1)

if __name__ == "__main__":
    main()
