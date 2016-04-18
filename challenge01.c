// compile: gcc challenge01.c -std=99 -lgmp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int hex2decimal(char hex) {
   if ('0' <= hex && hex <= '9')
      return hex - '0';
   else if ('A' <= hex && hex <= 'Z')
      return hex - 'A' + 10;
   else
      return hex - 'a' + 10;
}

char decimal2base64(int decimal) {
   if (decimal < 26)
      return 'A' + decimal;
   else if (decimal < 52)
      return 'a' + decimal - 26;
   else if (decimal < 62)
      return '0' + decimal - 52;
   else if (decimal < 63)
      return '+';
   else
      return '/';
}

void reverse(char* string) {
   int i = 0;
   int j = strlen(string) - 1;
   while (i < j) {
      char temp = string[i];
      string[i] = string[j];
      string[j] = temp;
      i++;
      j--;
   }
}

void main() {
   char* hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   mpz_t decimal;
   mpz_init(decimal);
   int exponent = 0;
   for (int i = strlen(hex)-1; i >= 0; i--) {
      int number = hex2decimal(hex[i]);
      // decimal += number * (int)Math.pow(16, exponent);
      mpz_t power;
      // mpz_t must be initialized before mpz_ui_pow_ui()
      mpz_init(power);
      mpz_ui_pow_ui(power, 16, exponent);
      mpz_addmul_ui(decimal, power, number);
      // printf("hex: %c, number: %d, exponent: %d, decimal: ", hex[i], number, exponent);
      // mpz_out_str(stdout, 10, decimal);
      // printf("\n");
      exponent += 1;
   }

   char* builder = malloc(sizeof(strlen(hex)));
   int divider = 64;
   mpz_t number;
   mpz_init_set(number, decimal);
   int index = 0;
   while (mpz_cmp_ui(number, divider) > 0) {
      mpz_t quotient;
      int remainder = mpz_tdiv_q_ui(quotient, number, divider);
      char letter = decimal2base64(remainder);
      builder[index] = letter;
      index++;
      mpz_set(number, quotient);
   }
   mpz_t quotient;
   int remainder = mpz_tdiv_q_ui(quotient, number, divider);
   char letter = decimal2base64(remainder);
   builder[index] = letter;
   index++;
   builder[index] = '\0';
   char* result = malloc(sizeof(strlen(builder)+1));
   strcpy(result, builder);
   reverse(result);
   puts(result);
   char* base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
   printf("hex:     %s\n", hex);
   printf("decimal: ");
   mpz_out_str(stdout, 10, decimal);
   printf("\n");
   printf("base64:  %s\n", base64);
   printf(strcmp(result, base64) == 0 ? "passed\n" : "failed\n");
}
