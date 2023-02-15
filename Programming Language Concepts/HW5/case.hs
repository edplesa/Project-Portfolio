--
-- Author: Edward Plesa
-- Homework 5
--

a = putStrLn "Called function a"

b = putStrLn "Called function b"

c = putStrLn "Called function c"

d = putStrLn "Called function d"


selector arg 
         | arg == 'a' = a
         | arg == 'b' = b
         | arg == 'c' = c
         | arg == 'd' = d
         | otherwise = putStrLn "Invalid argument returning..."
           



main = do
       putStrLn "Enter a or b or c or d"
       arg <- getLine
       selector (head arg)
