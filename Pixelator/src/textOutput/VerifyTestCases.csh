#!/usr/bin/tcsh -f

#
# verify the output of the test cases
# 

debug/TextOutput.exe > newTestCaseOutput.txt

diff TestCaseOutput.txt newTestCaseOutput.txt

