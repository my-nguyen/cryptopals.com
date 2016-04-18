import java.math.BigInteger;

class challenge01 {
   static int hex2decimal(char hex) {
      if ('0' <= hex && hex <= '9')
         return hex - '0';
      else if ('A' <= hex && hex <= 'Z')
         return hex - 'A' + 10;
      else
         return hex - 'a' + 10;
   }

   static char decimal2base64(int decimal) {
      if (decimal < 26)
         return (char)('A' + decimal);
      else if (decimal < 52)
         return (char)('a' + decimal - 26);
      else if (decimal < 62)
         return (char)('0' + decimal - 52);
      else if (decimal < 63)
         return '+';
      else
         return '/';
   }

   public static void main(String[] args) {
      String hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
      BigInteger decimal = BigInteger.ZERO;
      int exponent = 0;
      for (int i = hex.length()-1; i >= 0; i--) {
         int number = hex2decimal(hex.charAt(i));
         // decimal += number * (int)Math.pow(16, exponent);
         decimal = decimal.add(BigInteger.valueOf(number).multiply(BigInteger.valueOf(16).pow(exponent)));
         // System.out.println("hex: " + hex.charAt(i) + ", number: " + number + ", exponent: " + exponent + ", decimal: " + decimal);
         exponent += 1;
      }

      StringBuilder builder = new StringBuilder();
      BigInteger divider = BigInteger.valueOf(64);
      BigInteger number = decimal;
      while (number.compareTo(divider) > 0) {
         int remainder = number.mod(divider).intValue();
         char letter = decimal2base64(remainder);
         builder.append(letter);
         number = number.divide(divider);
      }
      int remainder = number.mod(divider).intValue();
      char letter = decimal2base64(remainder);
      builder.append(letter);
      String result = builder.reverse().toString();
      System.out.println(result);
      String base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
      System.out.println("hex:     " + hex);
      System.out.println("decimal: " + decimal);
      System.out.println("base64:  " + base64);
      System.out.println(result.equals(base64) ? "passed" : "failed");
   }
}
