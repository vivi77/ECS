ko_output="\033[31m"
ok_output="\033[32m"
warning="\033[33m"
rev_vid="\033[7m"

function colored_echo() {
  echo -e "$1$2\033[0m"
}

# $1: file where output had been redirected
function show_output() {
  echo "Output:"
  cat $1
  echo "==================="
}

# $1: Message which show expected output
function show_expectation() {
  echo "Expected:"
  echo -e $1
  colored_echo $ko_output "[ OUTPUT KO ]"
}
