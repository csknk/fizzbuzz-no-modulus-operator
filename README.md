FizzBuzz in C - without the Modulus Operator
============================================
FizzBuzz - iterate over a range of numbers and print:

* "Fizz" if the number is divisible by 3.
* "Buzz" if the number is divisible by 5.
* "FizzBuzz" if the number is divisible by both 3 and 5.
* The number if it is not divisible by either 3 or 5.

For the purposes of this exercise, use of the modulus operator `%` is disallowed. There's no particular reason for this - it's just an exercise.

Divisibility by Three
---------------------
This can be determined by comparing the sum of odd binary digits (mod 3) with the sum of even binary digits (mod 3). If these values are equal, then the number is divisible by 3.

### Example 1

42

Represented in binary digits, "even" bits marked:
```
↓   ↓   ↓
1 0 1 0 1 0
```

Sum of odd bits = `0 + 0 + 0 ≡ 0 mod 3`

Sum of even bits = `1 + 1 + 1 ≡ 0 mod 3`

These are equal, so 42 is divisible by 3.

### Example 2

43

Represented in binary digits, "even" bits marked:
```
↓   ↓   ↓
1 0 1 0 1 1
```

Sum of odd bits = `0 + 0 + 1 ≡ 1 mod 3`

Sum of even bits = `1 + 1 + 1 ≡ 0 mod 3`

These are not equal, so 42 is divisible by 3.

This algorithm still requires you to calculate the modulus of the sum of bits. Because the operand will have limited size, we can compute this by repeated subtraction. For a 32 bit integer, the maximum size of the operand will be 16 (i.e. the sum of 16 bits) which requires a maximum 5 subtractions.

```c
#include <stdio.h>
#include <stdint.h>
#include "integer-input.h"

#define BITS_IN_BYTE 8

/**
 * Determine mod 3 of input without using modulus operator.
 * Input should not be a large number - in this context it will
 * be at most 16 (assuming a 4 byte integer, this function will
 * receive at most the sum of 16 bits (i.e. 16)
 * */
uint8_t mod_3(int input)
{
	uint8_t result = 0;
	while (input >= 3) {
		input -= 3;
	}
	result = input;
	return result;
}

/**
 * Check that an integer x is divisible by 3 without using the modulus
 * operator.
 *
 * For a number to be divisible by 3, the sum of the odd bits mod 3 should equal
 * the sum of the even bits mod 3.
 * */
uint8_t divByThree(int x)
{
	unsigned mask_1 = 1u;
	unsigned mask_2 = 2u;
	int oddSum = 0;
	int evenSum = 0;
	// Because the mask shifts 2 bits to the left each iteration,
	// we only need to iterate half the number of bits times.
	for (size_t i = 0; i < (sizeof(x) * BITS_IN_BYTE) / 2; i++) {
		if (x & mask_1) {
			oddSum++;
		}
		if (x & mask_2) {
			evenSum++;
		}
		mask_1 <<= 2;
		mask_2 <<= 2;
	}
	return mod_3(oddSum) == mod_3(evenSum) ? 1 : 0; 
}
```
An alternative algorithm to determine divisibility by three:

* Sum all decimal digits in the number.
* Repeat the summation of digits until a single digit remains.
* If this value is divisible by 3, the original number is divisible by 3.

Divisibility by Five
--------------------
A number is divisible by five if it's least significant decimal digit is either 5 or 0:

```c
/**
 * A number is divisible by 5 if the least significant decimal digit is either 5 or 0.
 * */
uint8_t divByFive(int x)
{
	uint8_t finalDecimalDigit = x - ((x / 10) * 10);
	return finalDecimalDigit == 5 || finalDecimalDigit == 0 ? 1 : 0;
}
```
FizzBuzz
--------
Both our divisibility functions return 1 if the number is divisible and 0 if not. This makes it straightforward to perform the necessary logic to implement FizzBuzz:

```c
void fizzBuzz(int inputInteger)
{
	for (uint8_t n = 1; n <= inputInteger; n++) {
		if (divByFive(n) && divByThree(n)) {
			printf("%d: FizzBuzz\n", n);
			continue;
		}
		if (divByThree(n)) {
			printf("%d: Fizz\n", n);
			continue;
		}
		if (divByFive(n)) {
			printf("%d: Buzz\n", n);
			continue;
		}
		printf("%d\n", n);
	}
}

```
