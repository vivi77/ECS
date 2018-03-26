# Parser

A policy-based implementation of a Pratt parser.
Its particularity is that it can be reused as an `InputProducer` policy of an
other parser.

## Usage

You should provide 2 structures (or class).
The 1st one must respect the concept class *InputProducer*
It must have the following characteristics:

  - 3 types named *Output*, *Type* and *Precedence*:
    * Output: The data that the producer (aka. InputProducer) generates.
    * Type: An enum with all possible tags that can be associated with *Output*.
    * Precedence: An enum (or an integer type) that give parsing priority.
  - 2 methods:
    * parseExpression: Parse the next valid expression.
    * reset: Clear all the product in the producer
  - 1 static method:
    * getOutputType: Helper function that extract the type `Type` from your type `Output`

The 2nd one must respect the concept class *ParserPolicy*
It must have the following characteristics:

  - 2 types named *Precedence* and *Output*:
    * Precedence: An enum (or an integer type) that give parsing priority of your parser
    * Output: The data that your parser produce.
  - 1 static method:
    * getDefaultPrecedence: Returns the lowest priority of your parser

Then create a new type using *Parser* and your 2 policies, like this:
  `using <newType> = lel::Parser<YourInputProd, YourParserPolicy>;`

If one of those concept are not respected the compiler will generate errors
because of `static_assert` in those concept classes
