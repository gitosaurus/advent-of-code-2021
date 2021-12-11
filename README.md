# advent-of-code-2021
My answers to the Advent of Code 2021

## Notes about style

Virtually all style guides have variable declarations on their own line,
except for a in a `for` loop.  But there are certain C++ idioms where I
think it makes sense to do the same.  Reading lines from input is one of them:

```string line; while (getline(cin, line)) {```

