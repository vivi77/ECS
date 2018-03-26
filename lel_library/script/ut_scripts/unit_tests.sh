#!/bin/sh

dir=`dirname $0`
. $dir/ut_prints.sh

bin=""
log_file=""

# $1: Expected return value
# $2: Condition on results
# $3: Output expectation
function checker() {
  if [ $? -eq $1 ]; then
    colored_echo $ok_output "[ RETURN VALUE OK ]"
    show_output "$log_file"
    if `eval $2`; then
      colored_echo $ok_output "[ OUTPUT OK ]"
    else
      show_expectation "$3"
    fi
  else
    colored_echo $ko_output "[ RETURN VALUE KO ]"
  fi
}

function display_and_eval() {
  if [ $# -eq 1 ]; then
    colored_echo $rev_vid "$1"
    eval $1
  fi
}

# $1: Command to launch test
# $2: Expected return value
# $3: Test to do after command execution
# $4: Output expectation
function make_test() {
  display_and_eval "$1"
  checker $2 "$3" "$4"
}

if [ -z $bin ] || [ -z $log_file ]; then
  (>&2 echo "Missing binary name and log file name. Please complete script.")
  exit 1
fi

if [ ! -e $bin ]; then
  make -C ..
fi

function check_usage() {
  [ `grep -i 'usage' $log_file | wc -l` -eq 1 ]
}
