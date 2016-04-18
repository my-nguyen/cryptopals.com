def hex2decimal(hex):
   if ('0' <= hex and hex <= '9'):
      return ord(hex) - ord('0')
   elif ('A' <= hex and hex <= 'Z'):
      return ord(hex) - ord('A') + 10
   else:
      return ord(hex) - ord('a') + 10

def decimal2base64(decimal):
   if (decimal < 26):
      return chr(ord('A') + decimal)
   elif (decimal < 52):
      return chr(ord('a') + decimal - 26)
   elif (decimal < 62):
      return chr(ord('0') + decimal - 52)
   elif (decimal < 63):
      return '+'
   else:
      return '/'

hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
decimal = 0
exponent = 0
for i in range(len(hex)-1, -1, -1):
   number = hex2decimal(hex[i])
   decimal += number * (16**exponent)
   # print "hex: ", hex[i], ", number: ", number, ", exponent: ", exponent, ", decimal: ", decimal
   exponent += 1

builder = ""
divider = 64
number = decimal
while (number > 0):
   remainder = number % divider
   letter = decimal2base64(remainder)
   builder += letter
   number /= divider
result = builder[::-1]
print(result)
base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
print "hex:    ", hex
print "decimal:", decimal
print "base64: ", base64
print ("passed" if result == base64 else "failed")
