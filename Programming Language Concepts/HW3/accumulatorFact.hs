-- Function for accumulated factorial is taken directly from the
-- basics.pdf as per slide 10
factorial n = let loop acc n' = if n' > 1
                                then loop (acc * n') (n' - 1)
                                else acc
              in loop 1 n

main = print(factorial 100)