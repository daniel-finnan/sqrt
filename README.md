# sqrt

This is a C++ program for calculating the $\sqrt{42}$ using the standard library, but not using `cmath` or the `sqrt` function itself.

Calculating the square root using a floating point type quickly introduces errors into the result if we want any considerable number of decimal places. There is some decimal type support for C++, but it doesn't appear to be have been included into the language standards (see [here](https://www.open-std.org/JTC1/SC22/WG21/docs/papers/2012/n3407.htm) and [here](https://www.open-std.org/JTC1/SC22/WG21/docs/papers/2014/n3871.html)).

To avoid using floating point types, my code uses rational numbers in the calculations instead, since integer arithmetic doesn't introduce the same error. The algorithm used is known as [Heron's method](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Heron's_method). This wasn't selected as such, I simply started coding and thought this would be a quick and easy method to approximate the square root. There are faster algos for this.

## Procedure

1. Loop through the whole numbers from 1 to 42.
2. Find two consecutive numbers that when squared give us a result either side of 42.
3. Pass these into a recursive function.
4. In the recursion, find the mid-point between the two numbers.
5. Square the mid-point, and the two numbers, then compare them to see which fall either side of 42. Continue the recursion in this fashion.
6. Stop the recursion when a certain level of precision is reached.
7. From the two candidate numbers, determine which yields a result closest to 42.
8. You have the answer to "Life, the universe, and everything"!

## Caveats

- This code only works for non-negative integer numbers.
- The level of precision obtained is hardcoded, and depends on reaching the limit of the `long long int` type. There are more elegant ways to deal with the integer overflow.
- It hasn't been extensively tested.

## Result

- The answer is returned as both a rational number and then converted to a `double` for a decimal:

$\frac{13917284679}{2147483648}$

6.48074069945141673088073730469






