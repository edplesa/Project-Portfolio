import System.Environment   
import System.Exit
import Data.List

--
-- Author: Edward Plesa
-- Homework 4/ Project 2
--

writeToFile list = do
              writeFile "directory" list

program cmd list
         | cmd == 'x' = do                                               
                        putStrLn "You have chosen to exit"
         | otherwise = do                       
                   putStrLn "Enter (a) to add, (r) to remove, (l) to list, or (x) to exit"
                   line <- getLine                             
                   let newList = handle (head line) (drop 2 line) list                   
                   handle2 (head line) list                   
                   program (head line) newList


removeFromList index list = let (lf, lb) = splitAt index list in lf ++ tail lb


handle cmd input list                    
          | cmd == 'a' = do                         
                         sort (list ++ [input])
          | cmd == 'r' = do                        
                         removeFromList (read input :: Int) list
          | otherwise = do
                        sort (list)

handle2 cmd list            
          | cmd == 'x' = do
                         writeToFile (unlines list)
                         --putStr ""                  
          | cmd == 'a' = do
                         putStrLn "You have chosen to add.\n"
          | cmd == 'r' = do
                         putStrLn "You have chosen to remove.\n"
          | cmd == 'l' = do
                         putStrLn "You have chosen to list."
                         mapM_ print (zip[0..] list) 
                         putStrLn ""
          | otherwise = do
                         putStrLn "Invalid input.\n"


main = do
    args <- getArgs
    file <- if null args
        then do putStr "File: " ; getLine
        else pure (head args)
    putStr "Processing "
    putStrLn file
    directories <- readFile file
    let list = sort (lines directories)
    program ' ' list    
    putStrLn "Done"