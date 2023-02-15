import Data.List

--
-- Author: Edward Plesa
-- Homework 5
--

findTheA [] = []
findTheA (x:xs)
              | head x == 'A' = x : findTheA xs
              | otherwise = findTheA xs
