# Class 3

See also the Scala intro in the [Scala setup instructions](https://github.com/nyu-pl-fa22/in-class-scala).

## Control Flow

*Control flow* determines the order in which things get done in a
program. The primary mechanisms for control flow are:

* *Sequencing*: execute statements or evaluate expressions in
  sequential (or other explicitly specified) order
  
* *Selection* or *alternation*: make a choice based on some condition at run-time
  * conditional statements (`if` statements)
  * `choice` statements (aka `match` or `switch` statements)

* *Iteration*: execute a piece of code repeatedly
  
  * iterate until some condition is met (e.g. `while` loop)
  * iterate a fixed number of times (e.g. `for` loop)
  * iteration over collections

Additional mechanisms for control flow include

* *Procedural abstraction*: use a subroutine to parameterize and
  encapsulate a collection of control constructs

* *Recursion*: self-referencing expressions or subroutines

* *Concurrency*: execution of two or more program fragments *at the
  same time*

* *Exception handling* and *speculation*: program execution is
   interrupted and execution is transferred to a special handler

* *Nondeterminism*: order or choice of statements is deliberately
  unspecified

* *Continuation*: save and later return to a specific point in a
  computation
  
We will look at these advanced mechanisms throughout the
semester. Today's focus will be on the primary control flow mechanisms
listed above.

### Sequencing

Sequencing is a broad term that includes several specific sub-categories:

* Expression evaluation (dominant form of control in functional languages)
* Execution of consecutive statements (imperative languages)
* Explicit goto statements (unstructured control flow)

#### Expression evaluation

What is an expression?

* a simple object
  * literal constant (e.g. `1`, `2.3`, `"Hello"`)
  * named constant (e.g. `null`)
  * named variable (e.g. `x`)
* a function application
  * applied to one or more arguments, each of which is an expression
  * built-in functions are called *operators*
  * arguments of an operator are called *operands*
  * number of operands is called the *arity* of the operator
    * unary operator: one argument
    * binary operator: two arguments
    * ...
  * notations include 
    * prefix for unary operators (e.g. `-x`)
    * postfix for unary operators (e.g. `x++`)
    * infix for binary operators (e.g. `x + y`)
    * mixfix for operators of higher arity (e.g. `b ? x : y`)

Most imperative languages use infix operator notation for binary
operators.

The advantage of infix notation is that it mirrors standard
mathematical notation (e.g. for arithmetic operations), which makes
programs easier to read.

However, the disadvantage of infix notation is that the order in which
expressions are evaluated can be ambiguous. For instance, consider
this expression in Scala:

```scala
6 + 2 * 3 > 2
```

Which of the following calculations does this expression correspond to?

* ```((6 + 2) * 3) > 2```
* ```(6 + (2 * 3)) > 2```
* ```6 + ((2 * 3) > 2)```
* ```6 + (2 * (3 > 2))```

The order in which different infix operators are evaluated in an
expression is determined by *operator precedence*. Operators with
higher precedence *bind more strongly* and are evaluated before
operators with lower precedence. In Scala, `*` has higher precedence
than `+`, which in turn has higher precedence than `>`. So the example
is evaluated as

```scala
(6 + (2 * 3)) > 2
```

If we use two infix operators of the same precedence consecutively
(note: using the same operator twice is a special case), then the
evaluation order is determined by *operator associativity*. For
instance, consider the following Scala expression:

```scala
6 * 4 * 2 / 3 % 2
```

In Scala, the operators `*`, `/`, and `%` all have the same
precedence. They are also all *left-associative* which means that they
are evaluated left-to-right when they are applied in a sequence as in
the example above. That is, the example expression is evaluated as

```scala
(((6 * 4) * 2) / 3) % 2
```

Operators that are right-associative on the other hand are evaluated
in right-to-left order.

As we discussed earlier, context-free grammars can be used to encode
operator precedence and associativity of programming languages.

Be aware that operator precedence and associativity vary among
languages. Moreover, some languages allow operator overloading and
even redefinition of precedence and associativity of operators, which
further complicates matters (Scala allows operator overloading but the
precedence and associativities of operators are fixed). If in doubt,
check the language specification or use explicit parenthesis.

#### Statements and Side Effects

If the evaluation of an expression influences subsequent computation
in some other way besides returning a value, this is called a *side
effect*.

Examples of side effects include

* modifying the value of a variable (assignment)
* writing to a file on disk
* sending a package to the network
* printing to standard output
* more generally, any system call that effects the state of the
  environment.
  
*Imperative languages* include expressions that have side effects
(e.g. assignments `x = 2 + 1`). Expressions whose sole purpose is
their side effect and whose result value does not matter are called
*statements*. Imperative programming means programming by composing
statements and is therefore also referred to as *computing by means of
side effects*.

*Purely functional languages* on the other hand are languages in which
expressions have no side effects. These languages are also referred to
as being *referentially transparent*, meaning that it is possible to
replace any expression in a program with the value that it computes
without changing the behavior of the program.

Classification of some languages (imperative vs. functional)
* Imperative: C, Pascal
* Mostly imperative: Java, C#, Python, Ruby
* Mostly functional: Scala, OCaml, Lisp, Scheme
* Purely functional: Haskell, Miranda

Imperative languages often make a syntactic distinction between
statements and expressions. Instead, functional languages that allow
side effects typically distinguish an expression and a statement on the
semantic level based on the type of the return value that the
expression produces. For instance, in Scala any expression that
returns the value `()` of type `Unit` can be viewed as a
statement. Statements in OCaml can be defined similarly.


#### L-values and R-values

Expressions that denote memory locations are called
*l-values*. Expressions that denote values stored at memory locations
are called *r-values*.

There are two prevalent *memory models* that programming languages use
to determine what is an l-value and what is an r-value: the *value
model* and the *reference model*.

##### Value Model

The value model can be summarized as follows:

* The same expression can be an l-value or r-value depending on its context

* A mutable variable appearing on the right side of an assignment is
  an r-value, i.e. it is used as a name for the *value* stored at the
  memory location associated with that variable.

* A variable appearing on the left side of an assignment is an
  l-value, i.e. it is used as a name for the memory location
  associated with that variable.

For example, C and C++ use the value model and so does Scala:

```scala
var a = 0
a = a + 1
```

Here, the occurrence of `a` on the left side of `=` is an l-value
because it refers to the memory location bound to the variable `a`. The occurrence
of `a` on the right side of `=` in the last line is an r-value as it
refers to the current value stored in the memory location bound to `a`.

##### Reference Model

The reference model can be summarized as follows:

* Every using occurrence of a variable is an l-value.

* To get the value at the named location, the variable must be
  explicitly *dereferenced*.

For example, OCaml uses the reference model for mutable variables:

```ocaml
let a = ref 0 in
a := !a + 1
```

Here, `ref 0` creates a memory location that is initialized to value `0`. This
location is bound to the name `a`. The expression `!a` dereferences
the l-value `a` to retrieve the value `0` stored at the location named
by `a`.


### Structured and Unstructured Control Flow

In machine language, there are no conditional statements or
loops. Instead, we only have *branch instructions*, which transfer
control from the current program point to another. We refer to this as
*unstructured control flow*. Branch instructions can be unconditional
or conditional (on a very simple condition, e.g. checking whether the
value of a particular CPU register is `0`).

With branch instructions, we can implement loops, conditional
statements, and choice statements. In fact, we only need
* increment by 1
* decrement by 1
* branch on 0
to build a universal machine (one that is Turing complete).

Some high-level languages such as C support unstructured control flow
by using `goto` statements which act like unconditional branch
instructions.  However, most modern programming languages don't
support such constructs anymore because unstructured control flow can
lead to confusing programs, which are prone to bugs (see [*Go To Statement Considered Harmful* by Edgar Dijkstra](https://homepages.cwi.nl/~storm/teaching/reader/Dijkstra68.pdf)).

Structured alternatives to `goto` statements include
* Selection: structured branching
* Sequencing or grouping: compose multiple statements together so that
  they are executed in sequence.
* Iteration: general-purpose loop constructs
* Exit from subroutine: explicit return statements
* Exit from loop: explicit `break` or `continue` statements
* Return from nested subroutine: some languages support this explicitly
* Exceptions: Language mechanisms for error handling


#### Selection

All programming languages support some form of selection mechanism to
choose between two or more alternatives. The most common selection
constructs of this type are conditional statements (or conditional
expressions), which allow one to choose between two alternative
statements (expressions) based on whether a given condition holds.

For instance, in C we have `if` statements

```c
if (condition) statement1 else statement2
```

which execute `statement2` if the expression `condition` evaluates to
`0` and `statement1` otherwise. Similarly, we have conditional
expressions in C which take the form

```c
condition ? expression1 : expression2
```

and evaluates to the result of `expression2` if `condition` evaluates
to `0` and to the result of `expression1` otherwise.

Other languages use different syntax for the same construct. For
instance, in Ada conditional statements take the form:

```ada
if condition then
  statement1
else
  statement2
end if
```

Scala (v. 3.0 and newer) uses a similar syntax as Ada but does not distinguish between
conditional statements and conditional expressions:

```scala
if condition then 
  expression1 
else 
  expression2
```
It also supports a semantically equivalent C-like syntax
```scala
if (condition) {
  expression1 
} else {
  expression2
}
```

In most languages, the `else` branch of conditional statements can be omitted.

#### Statement Grouping

* Pascal introduced `begin`-`end` pairs to group a sequence of
  statements in a block that can be viewed again as a single statement.

* C, C++, Java abbreviate the `begin`-`end` pairs to `{ }`.

* Ada dispenses with braces for blocks, because keywords for the
  enclosing control structure are sufficient. Example

  ```ada
  for J in 1..N loop statement1; statement2 end loop
  ```

  This requires more writing but is more readable.

* Another possibility - make indentation (white space) significant
  (e.g., ABC, Python, Haskell).

* Scala supports both braces `{ }` for blocks and (since v. 3.0) an alternative indentation-based notation.

#### Short-circuit evaluation

Consider the following Scala code:

```scala
if x / y > 5 then z = 6
```
What if `y == 0`? We can test for `0` before doing the division:

```scala
if y != 0 && x / y > 5 then z = 6
```

But don't binary operators like `&&` normally evaluate both operands?

Solutions:
* a lazy evaluation rule for logical operators (Scala, Java, C, Lisp, ...)

  ```scala
  C1 && C2     // don't evaluate C2 if C1 is false
  C1 || C2     // don't evaluate C2 if C1 is true
  ```

* a control structure with a different syntax (Ada)

  ```ada
                              -- don't evaluate C2
      if C1 and then C2 then  --   if C1 is false
      if C1 or else C2 then   --   if C1 is true
  ```

#### Multiway selection

A choice statement (or choice expression) is needed when there are many
possibilities *at the same logical level* (i.e. depending on the same
condition).

Here is how we would write a choice statement in Ada:

```ada
case Next_Char is
  when 'I' => Result := 1;
  when 'V' => Result := 5;
  when 'X' => Result := 10;
  when 'C' => Result := 100;
  when 'D' => Result := 500;
  when 'M' => Result := 1000;
  when others => raise Illegal_Numeral;
end case;
```

In Scala, we use `match` expressions for multiway selection:

```scala
nextChar match 
  case 'I' => result = 1
  case 'V' => result = 5
  case 'X' => result = 10
  case 'C' => result = 100
  case 'D' => result = 500
  case 'M' => result = 1000
  case _ => throw Illegal_Numeral
```

Since Scala does not distinguish expressions and statements syntactically, we can
also write the above code as follows:

```scala
result = nextChar match
  case 'I' => 1
  case 'V' => 5
  case 'X' => 10
  case 'C' => 100
  case 'D' => 500
  case 'M' => 1000
  case _ => throw Illegal_Numeral
```

Choice statements can be simulated by a sequence of conditional
statements, but the logic is obscured. Moreover, choice statements can
often be translated more efficiently to machine language than a
sequence of conditional statements. Specifically, in C/C++/Java/Ada
style choice statements, we always have a finite set of possible
choices to select from, which can be determined at compile time:

* build table of addresses, one for each choice
* compute value of expression on which we select
* transform value into table index
* get table element at index and branch to that address
* execute statement for selected choice
* branch to end of the choice statement

This is not the typical implementation for a Scala/OCaml/Haskell style
choice expressions. As we shall see later this semester, these languages
support more powerful choice expressions that involve a more complex
translation to machine language.

##### Fall-through semantics of choice statements

C's choice statement, called `switch`, has a special *fall-through*
semantics that you should be aware of. Consider the following
literal translation of our earlier example from Scala to C:

```c
switch (next_char) {
  case 'I': val = 1;
  case 'V': val = 5;
  case 'X': val = 10;
  case 'C': val = 100;
  case 'D': val = 500;
  case 'M': val = 1000;
  default: Illegal_Numeral = true;
}
```

This code does not have the intended behavior: it will always set
`Illegal_numeral` to `true`. The fall-through semantics of `switch`
means that once a case of the `switch` statement has been taken, if
that case is not terminated by an explicit `break` statement, the next
case in the switch statement will be executed. For instance, if
`next_char` has value `D`, then we will first take the case that sets
`val` to `500` as expected. However, since that case is not terminated
by `break`, we continue with the next case and set `val` to
`1000`. Since that case is also not terminated by `break`, we continue
further to the `default` case and set `Illegal_Numeral` to `true`.

Here is the correct C-version of our example code:

```c
switch (next_char) {
  case 'I': val = 1; break;
  case 'V': val = 5; break;
  case 'X': val = 10; break;
  case 'C': val = 100; break;
  case 'D': val = 500; break;
  case 'M': val = 1000; break;
  default: Illegal_Numeral = true;
}
```

One instance where the fall-through semantics of `switch` is useful
is [*Duff's device*](https://en.wikipedia.org/wiki/Duff%27s_device),
which is an efficient implementation for copying a memory block from
one location to another.

As a motivation, consider the following simple C function to copy a
block of `int` values of size `count` from location `to` to location
`from`:

```c
void send(int* to, int* from, int count) {
  do *to++ = *from++; 
  while (--count > 0);
}
```

Note that this code is equivalent to the following, more elaborate, C code:

```c
void send(int* to, int* from, int count) {
  do {
  *to = *from;
  to = to + 1;
  from = from + 1;
  count = count - 1;
  while (count > 0);
}
```

This code is quite inefficient: it requires the execution of a
conditional branch after each `int` value has been copied, which is
bad for performance. CPUs use instruction pipelines to start the
execution of subsequent instructions before the execution of the
current instruction has been completed. This, however, only works well
if the CPU knows what the next instructions are. This information is
difficult to determine if the current instruction is succeeded by a
conditional branch.

One idea to make the loop more efficient is to use loop unrolling,
e.g., copy 8 `int` values in a single loop iteration so that we only
have to branch every 8 instructions:

```c
void send(int* to, int* from, int count) {
  do {
    *to++ = *from++; *to++ = *from++; 
    *to++ = *from++; *to++ = *from++; 
    *to++ = *from++; *to++ = *from++; 
    *to++ = *from++; *to++ = *from++; 
    count -= 8;
  } while (count > 0);
}
```

Though, what if `count` is not a multiple of 8?

This is where Duff's device comes into play. The idea is to arrange
the 8 assignments in a `switch` statement so that before entering the
loop, we execute the `count % 8` remaining assignments using the
fall-through semantics of `switch`. Then we execute the loop `(count +
7) / 8` times to copy all other values, 8 `int` values at a time. 

What Duff realized is that the C syntax allows one to interlace the
body of the `switch` statement with the body of a do-while loop,
allowing the `switch` statement to jump into the middle of the loop
body. This leads to the following unexpected implementation that
correctly copies the complete memory block:

```c
void send (int* to, int* from, int count) {
  int n = (count + 7) / 8;
  switch (count % 8) {
    case 0: do { *to++ = *from++;
    case 7:      *to++ = *from++;
    case 6:      *to++ = *from++;
    case 5:      *to++ = *from++;
    case 4:      *to++ = *from++;
    case 3:      *to++ = *from++;
    case 2:      *to++ = *from++;
    case 1:      *to++ = *from++;
               } while (--n > 0);
  }
}
```

Allegedly, Duff announced his discovery with "a combination of pride
and revulsion".

It should be noted that, while Duff's device is an interesting example
of using fall-through semantics, modern C compilers will likely
produce better machine language translations for more straightforward
implementations of the memory copy task. Moreover, the standard `C`
library provides a function `memcopy` for copying memory blocks that
is preferable to hand-coded functions as it uses architecture-specific
optimizations at the machine language level. So use `memcopy` if you
need to implement this kind of task in C.

#### Iteration

Iteration of statements is achieved using various loop constructs.
All loops can be expressed as `while` loops, which in
C/Scala/Java,... takes the form:

```scala
while (condition) statement
```

* `condition` is evaluated at each iteration

* if it evaluates to true, `statement` is executed and we repeat

* otherwise, the loop exits.

* if `condition` is initially `false`, `statement` is never executed.

Thus, we have that

```scala
while (condition) statement
```

is equivalent to

```scala
if (condition) { 
  statement;
  while (condition) statement 
}
```

Sometimes we want to check `condition` at the end of each iteration of
the loop instead of the beginning; this will guarantee that `statement` is
executed at least once. Most languages provide a special construct for
this type of loop. The two most common variants are:

* Pascal: ```do statement until condition```

* C/Java/...: ```do statement while (condition)```

Both variants execute `statement` at least once. The do-until loop exits when
`condition` is true whereas do-while exits when `condition` is false.

Scala supports neither do-until nor do-while loops directly, but one
can of course simulate those variants with a `while` loop and a Boolean
variable. For instance, a do-while loop can be encoded as:

```scala
var first = true;
while (first || condition) {
  statement
  first = false;
}
```

We will see later that one can extend Scala with proper do-while and
do-until loops using some advanced mechanisms that the language provides.

##### Breaking out of loops

A more common need is to be able to break out of the loop in the
middle of an iteration. Different languages provide different
statements to do this:

* C,C++,Java,...: `break`
* Perl: `last`
* Ada: `exit`

Example from C:

```c
while (true) {
  do some things;
  if (condition) break;
  do some more;
}
```

Sometimes we want to break out of several levels of nested
loops. In some languages including Ada, Perl, and Java, one can give names
to loops that can be used as targets of the `break` statement. Here is
an example in Java:

```java
outer: while (C1) {
  inner: while (C2) {
    do some things;
    if (major_failure) break outer; // exit outer loop
    if (minor_annoyance) break inner; // exit inner loop to 
                                     
  }
}
```

In C and C++ one needs to use a `goto` statement to break out of
nested loops.

Another related need is to skip the rest of the current loop iteration
anywhere within the loop and continue with the next iteration. In
C,C++,Java,... this can be achieved with the `continue` statement. Its
use is similar to `break` (including the use of named loops).

Scala does not support `break` or `continue` statements. However, they
can of course be simulated by introducing auxiliary Boolean variables
(or by using recursive functions instead of loops).

##### Definite Loops

Counting loops are used to iterate over discrete domains. Examples

* Ada: ```ada
for J in 1..10 loop statement end loop;```

* C, C++, Java, C#, ...: ```c
for (int j = 0; j < n; i++) statement```

Common design issues are

* evaluation of bounds
* scope of the loop variable
* empty loops
* increments other than 1
* backwards iteration
* non-numeric domains and iterators

For example, does the following Ada loop terminate?

```ada
for J in 1..N loop
   ...
   N := N + 1;
end loop;
```

Yes, because in Ada the bound of the loop (here `N`) is evaluated once
before the loop starts.

On the other hand, C, C++, C#, Java, ... have hybrid semantics:

```c
for (int j = 0; j < last; j++) {
   ...
   last++;
}
```

This loop does not terminate if `j < last` holds initially before the
loop enters. Since the condition `j < last` is evaluated in each
iteration of the loop, the condition remains true forever when `j` and
`last` are incremented in lock-step.

Another design choice is whether the loop variable is mutable within
the loop body and whether its scope is only the loop or the containing
block of the loop. Here is an Ada example

```ada
Count: integer := 17;
...
for Count in 1..10 loop
  ...
end loop;
Put_Line(Count);
```

This program will print `17` because in Ada the scope of the loop
variable `Count` is restricted to the loop itself. On the other hand,
in C# the scope of the loop variable is the surrounding block. So the
following C# code would yield a static semantic error:

```c#
{
  int count;
  {
    count = 17;   // use before declaration of loop variable
    for (int count = 0; count < 10; count++) {
      ...
    }
    Console.WriteLine(count);
  }
}
```

On the other hand, the following program will print `10`

```c#
{
  int count = 17;
  {
    for (int count = 0; count < 10; count++) {
      ...
    }
    Console.WriteLine(count); // loop variable still in scope
  }
}
```

Most languages support different increments of the loop variable. For
instance, a decrementing loop in Ada is expressed like this:

```ada
for J in reverse 1..N loop statement end loop
```

In C-style `for` loops one can use arbitrary statements for the loop
increment and even leave it out all together. Here is a C `for` loop
that iterates backwards from `10` to `0` in decrements of `2`:

```c
for (int i = 10; i > 0;) {
  ...
  i -= 2;
}
```

Many languages also allow for loops to be used for other discrete types
than just integers. Here is an Ada example:

```ada
type Days is (Mon, Tue, Wed, Thu, Fri, Sat, Sun);
... 
for D in Days loop ... end loop;
```

Java has a special `for` loop form that can be used to iterate over
collections. E.g. suppose `xs` is of type `List<Object>` then

```java
for (Object x : xs) statement
```

is expanded to

```java
for (Iterator<Object> iter = xs.iterator(); iter.hasNext();) {
  Object x = iter.next();
  statement
}
```

Languages such as Python and Scala generalize `for` loops to
expressions that compute new iterable collections from existing
ones. In Scala a `for` expression takes the form:

```scala
for x <- e1 yield e2
```

respectively

```scala
for x <- e1 do e2
```

In both cases, the `for` expression declares the variable `x` whose
scope is the entire expression. The expression `e1` must evaluate to
some form of collection type (e.g. a list) over which the `for`
expression iterates. In each iteration, `x` is bound to the next value
stored in `e1` and then evaluates the expression `e2`. The difference
between the two variants is that the `yield` version creates a new
collection that stores the values obtained from evaluating the
expression `e2` in each iteration. The result value of the `for`
expression is this new collection. The `do` variant instead simply
evaluates `e2` for the purpose of its side effect, similar to a normal
`for` loop. 

Here is a simple example that computes a collection holding the
squares of all values from `1` to `20`:

```scala
for x <- 1 to 20 yield x * x
```

And here is another example that simply prints all those squares:

```scala
for x <- 1 to 20 do println(x * x)
```

`for` expressions also allow to add filters that cause some of the
values in the collection that we iterate over to be skipped.  For
instance, the following Scala code uses this feature to compute the
sequence of prime numbers in the interval `[1,20]`:

```scala
def factors(x: Int) =
  for 
    i <- 1 to x if x % i == 0 
  yield i

def primes(xs: Range) = 
  for 
    x <- xs if factors(x) == List(1,x)
  yield x

primes(1 to 20)
```

