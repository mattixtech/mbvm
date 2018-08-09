#!/usr/bin/env python
"""
blackbox_test.py
Matthew Brooks, 2018
Tests mbvm using all of the programs in test_programs against their known
output.
"""
# For 2/3 compatible print()
from __future__ import print_function
from subprocess import Popen, PIPE

import json
import os
import sys


def test_program(program_name, expected_output, program_input=""):
    """
    Tests a program to make sure it outputs what we expect.

    :param program_name: the program to test
    :param expected_output: the expected output
    :return: 0 if passed 1 if failed
    """

    # For 2/3 compatibility
    # TODO: Perhaps the kwargs could be passed as an arg dict
    if sys.version_info >= (3,):
        p = Popen([mbvm_exec, os.path.join(test_programs_dir, program_name)],
                  stdin=PIPE, stdout=PIPE, stderr=PIPE, encoding='utf8')
    else:
        p = Popen([mbvm_exec, os.path.join(test_programs_dir, program_name)],
                  stdin=PIPE, stdout=PIPE, stderr=PIPE)

    received_output = p.communicate(program_input)[0]
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

    # TODO: Check JSON exceptions
    with open(os.path.join(test_programs_dir, "test_programs.json")) as f:
        test_programs_json = json.load(f)

    if test_programs_json:
        failed_tests = 0

        for test in test_programs_json["programs"]:
            if "input" in test:
                input_text = test["input"]
            else:
                input_text = "a"

            failed_tests += test_program(test["name"], test["expected_output"],
                                         program_input=input_text)

        if failed_tests:
            print("Errors: Failed '{}' tests!".format(str(failed_tests)))
        else:
            print("All tests passed!")
    else:
        sys.stderr.write("ERROR: No tests were found")
        sys.exit(1)


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
