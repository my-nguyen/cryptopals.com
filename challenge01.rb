def hex2decimal(hex)
   if ('0' <= hex && hex <= '9')
      return hex.ord - '0'.ord
   elsif ('A' <= hex && hex <= 'Z')
      return hex.ord - 'A'.ord + 10
   else
      return hex.ord - 'a'.ord + 10
   end
end

def decimal2base64(decimal)
   if (decimal < 26)
      return ('A'.ord + decimal).chr
   elsif (decimal < 52)
      return ('a'.ord + decimal - 26).chr
   elsif (decimal < 62)
      return ('0'.ord + decimal - 52).chr
   elsif (decimal < 63)
      return '+'
   else
      return '/'
   end
end

hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
decimal = 0
exponent = 0
(hex.length-1).downto(0) do |i|
   number = hex2decimal(hex[i])
   decimal += number * (16**exponent)
   # puts("hex: #{hex[i]}, number: #{number}, exponent: #{exponent}, decimal: #{decimal}")
   exponent += 1
end

builder = ""
divider = 64
number = decimal
while (number > 0)
   remainder = number % divider
   letter = decimal2base64(remainder)
   builder << letter
   number /= divider
end
result = builder.reverse
puts(result)
base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
puts("hex:     #{hex}")
puts("decimal: #{decimal}")
puts("base64:  #{base64}")
puts(result == base64 ? "passed" : "failed")
