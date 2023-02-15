-- Function for natural factorial is taken directly from the
-- basics.pdf as per slide 9
factorial n = if n > 1
			  then n * factorial (n-1)
			  else 1

main = print(factorial 100)