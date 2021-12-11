# advent-of-code-2021
My answers to the Advent of Code 2021

https://adventofcode.com/2021

## Choice of language

When this started, I thought I'd use it as a chance to learn OCaml or
Rust.  But the first and most important task every day was to read some
lines from a file, and in OCaml, this turned out to be a brainteaser on
its own, for me.  Simply put, I didn't have time this year.

The kind of input reading that these puzzles want is pretty simple for
C++.  To read a bunch of integers from standard input, for example:

```c++
copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(numbers));
```

So off I went!  Later puzzles seemed remarkably well-suited to C++
library classes like `bitset<N>`, or standard algorithms like
`partition`, for example, so I've continued in C++.

It'll be fun to have these as a reference for programming exercises
when I go back to learn OCaml or Rust, I hope.

## Dependencies

Every problem is compiled with C++11 out of the box, using only what's
in the standard library.

## Directory structure

Even though every day has the same `Makefile`, I keep a copy in each day's
subdirectory so that each one is self-contained.  The contents of each
day are:

  * `Makefile`
  * `sample.txt`:  the example input in the problem description
  * `input.txt`:  the official problem input
  * `part_1.cc`:  my solution to part 1 of the problem
  * `part_2.cc`:  my solution to part 2 of the problem

The problems are all solved like this:

```bash
./part1 < input.txt
./part2 < input.txt
```

There's one problem, the lantern-fish one, where the example text
talks about differing numbers of days, 18 vs. 80.  This is the one
case so far where the executable takes an optional command-line
argument.

## Notes about style

### Initialization

Virtually all style guides have variable declarations on their own
line, except for a in a `for` loop.  But there are certain C++ idioms
where I think it makes sense to do the same.  Reading lines from input
is one of them:

```c++
string line; while (getline(cin, line)) {
```

The idea here is that `line` is not meaningfully initialized until the
first call to `getline`, so why not put them on the same line, even
though it's two separate statements?  I know that pedantic IDEs will
send me to the corner for that, but this isn't production code.

Same goes for variables initialized from a stream using `>>`:

```c++
int one, two; ss >> one >> two;
```

### Globals

C++ doesn't have a "module" concept, nor does it have inner functions.
This means that any variables which are shared at a scope larger than
local have to be in a class or have to be global.  And of course,
within a library, global variables are kind of dangerous and
significant, so they're often indicated using uppercase.  But in these
self-contained puzzles, I didn't bother with different casing for
them, since the only reason I went global was because I didn't have
inner functions.

In many cases, I was able to use lambdas to do the job of inner
functions.
