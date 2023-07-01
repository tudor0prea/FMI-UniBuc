
module Main where

import System.IO

import Lab2
import Exp
import Parsing
import Sugar
import Printing
import REPLCommand
import Program
import qualified Data.Map.Strict as Map

main :: IO ()
main = execute Map.empty

execute env
  = do
    putStr "miniHaskell> "
    hFlush stdout
    s <- getLine
    case parseFirst replCommand s of
          Nothing -> putStrLn "Cannot parse command" >> execute env
          Just Quit -> return ()
          Just (Load file) -> do
            result <- parseFromFile program file
            case result of
              Left e  -> print e >> execute env
              Right pgm -> execute (programEnv pgm)
          Just (Eval es) ->
            case parseFirst exprParser es of
              Nothing -> putStrLn "Error: cannot parse expression" >> execute env
              Just e ->
                let simpleE = desugarExp e
                    simpleE' = normalizeEnv env simpleE
                    e' = sugarExp simpleE'
                 in putStrLn (showExp e') >> execute env
