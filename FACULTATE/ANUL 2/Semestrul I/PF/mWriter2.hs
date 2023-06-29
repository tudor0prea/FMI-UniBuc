import System.Win32 (xBUTTON1, COORD (yPos))

--- Monada Writer

newtype WriterS a = Writer { runWriter :: (a, [String]) }  -- > MODIFICAT cu []


instance  Monad WriterS where
  return va = Writer (va, []) -- > IN loc de "" avem []
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)


instance  Applicative WriterS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor WriterS where              
  fmap f ma = pure f <*> ma     

tell :: String -> WriterS () 
tell log = Writer ((), [log]) -- > [log] in loc de log
  
logIncrement :: Int  -> WriterS Int
logIncrement x = do
    tell( "increment: "++ show x ++ "\n")
    return( x+1)

logIncrement2 :: Int -> WriterS  Int
logIncrement2 x = do
    y<- logIncrement x
    logIncrement y

logIncrementN :: Int -> Int -> WriterS Int
logIncrementN x 1 =  logIncrement x 
logIncrementN x n = do
    y<- logIncrementN x (n-1)
    logIncrement y


            
