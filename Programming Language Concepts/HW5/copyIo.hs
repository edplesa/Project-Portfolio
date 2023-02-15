import System.Directory
import System.Environment
--
-- Author: Edward Plesa
-- Homework 5
--
main = do 
       fileArgs <- getArgs

       let file1 = fileArgs!!0
       let file2 = fileArgs!!1

       file1Exists <- doesFileExist file1
       file2Exists <- doesFileExist file2

       if (not file1Exists)
         then putStrLn "File 1 does not exist"
       else if (file2Exists)
         then putStrLn "File 2 does exist"
       else copyFile (file1) (file2)
       putStrLn "Done"
       
