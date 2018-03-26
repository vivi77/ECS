# CLIParser

Command Line Interface (CLI) parser.
Use [Parser](Parser.md)

## Usage

Use `parseExpression` to get an expression from the parser.
It will automatically prompt the user new input if there is not enough input to
generate a command.

## Expression types

Type     |       Real type       |
---------|-----------------------|
COMMAND  | lel::CmdOutput        |
ASSIGN   | lel::AssignOutput     |
OPTION   | lel::OptionOutput     |
TERMINAL | lel::TerminalOutput   |
EOL      | lel::EOLOutput (1)    |
CANCEL   | lel::CancelOutput (1) |

(1): These output carry no information

--------------------
lel::CmdOutput carry all the arguments and all the options given to a command.
These can be retrieve through the following methods:

  * getArgs(): Retrieve the arguments of a command
  * getOpts(): Retrieve the options of a command

The options can carry value or not
