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

/**
 * A number is divisible by 5 if the least significant decimal digit is either 5 or 0.
 * */
uint8_t divByFive(int x)
{
	uint8_t finalDecimalDigit = x - ((x / 10) * 10);
	return finalDecimalDigit == 5 || finalDecimalDigit == 0 ? 1 : 0;
}

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

int main()
{
	printf("Please enter an integer:\n");
	int inputInteger = 0;
	getIntegerFromStdin(&inputInteger);
	fizzBuzz(inputInteger);	
	return 0;
}
