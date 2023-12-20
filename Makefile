(input)=*./*.c
output=rana
rana:
	gcc -Wall -Werror -Wextra -pedantic ./*.c -o rana
