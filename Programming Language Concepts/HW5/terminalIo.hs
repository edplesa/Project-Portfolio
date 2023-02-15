import Data.Char
import Data.List

--
-- Author: Edward Plesa
-- Homework 5
--
          
getInput = do  
           input <- getLine
           return input


terminalIo :: IO Int
terminalIo = do
          putStrLn "Enter a number or '.'"
          input<-getInput
          if (not (input == "."))
             then do
                 let num = (read input::Int)
                 rest <- terminalIo             
                 return (num+rest)
          else do
             return 0
