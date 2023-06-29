import System.Process.Internals (ProcessHandle(mb_delegate_ctlc))
import Foreign (moveBytes, FinalizerEnvPtr)
import Distribution.Simple.PackageIndex (deletePackageName)
-- -- -- Laborator 13 PF -- -- --
    -- Monade - Introducere --

{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k   = k va
  Nothing >>= _   = Nothing


instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   



  -- ex. 0:
  return 3 :: Maybe Int
Just 3
(Just 3) >>= (\ x -> if (x>0) then Just (x*x) else Nothing)
--parametru >>= functie
Just 9
-}

-- ex. 1
pos :: Int -> Bool
pos  x = if (x>=0) then True else False

fct :: Maybe Int ->  Maybe Bool
fct  mx =  mx  >>= (\x -> Just (pos x))

fct mx = do
    x<-mx 
    return (pos x)


addM :: Maybe Int -> Maybe Int -> Maybe Int
addM Nothing _ = Nothing
addM _ Nothing = Nothing
addM (Just x) (Just y) = Just(x+y) 

addM1 :: Maybe Int -> Maybe Int -> Maybe Int
addM1 ma mb = do
    a<-ma 
    b<-mb 
    return (a+b)

-- ex.3
--cartesian_product xs ys = xs >>= ( \x -> (ys >>= \y-> return (x,y)))

cartesian_product ma mb = do
    a<-ma 
    b<-mb
    return (a,b)



--prod f xs ys = [f x y | x <- xs, y<-ys]
prod f ma mb = do
    a<-ma 
    b<-mb 
    return (f a b)

--citeste caractere pana la newline
myGetLine :: IO String
myGetLine = getChar >>= \x ->
      if x == '\n' then
          return []
      else
          myGetLine >>= \xs -> return (x:xs)

myGetLine2 = do
    x<-getChar
    if x=='\n' then
        return []
    else do 
        xs<-myGetLine2 
        return (x:xs)

-- ex. 4
prelNo noin =  sqrt noin

ioNumber = do
     noin  <- readLn :: IO Float
     putStrLn $ "Intrare\n" ++ (show noin)
     let  noout = prelNo noin
     putStrLn $ "Iesire"
     print noout


ioNumber2 = (readLn :: IO Float) >>= 
    \noin -> (putStrLn("Intrare \n" ++ show(noin))) 
    >>= (\_ -> let noout = prelNo noin in putStrLn("Iesire") 
    >>= (\_ -> print noout))


-- ex. 6
data Person = Person { name :: String, age :: Int }

showPersonN :: Person -> String
showPersonN (Person n _)= "Name: " ++ n  -- daca e caracter nu e nev de show
showPersonA :: Person -> String
showPersonA (Person _ a)= "Age: " ++ show(a) -- daca este numar ii facem show
                                                -- ca sa il aducem la string

{-
showPersonN $ Person "ada" 20
"NAME: ada"
showPersonA $ Person "ada" 20
"AGE: 20"
-}

showPerson :: Person -> String
showPerson (Person n a) = "(Name: " ++ n ++ " Age: " ++ show(a) ++ ")"

{-
showPerson $ Person "ada" 20
"(NAME: ada, AGE: 20)"
-}


newtype Reader env a = Reader { runReader :: env -> a }


instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  (>>=) :: Reader env a -> (a -> Reader env b) -> Reader env b
  ma >>= k = Reader f
    where f env = let a = runReader ma env
                  in  runReader (k a) env



instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance Functor (Reader env) where              
  fmap f ma = pure f <*> ma    

-- definim functia "ask" ce ne permite sa avem acces la env
ask:: Reader env env 
ask= Reader( \env-> env)

mshowPersonN ::  Reader Person String
mshowPersonN = do
    person<-ask     --luam persoana din env
    return ("Name: " ++ name person)

mshowPersonN2 :: Reader Person String
mshowPersonN2 = do 
    Person n _ <- ask
    return ("Name: " ++ n)


mshowPersonA ::  Reader Person String
mshowPersonA = do
    person<-ask
    return ("Age: "++ show(age person))

mshowPerson ::  Reader Person String
mshowPerson = do
    n<- mshowPersonN
    a<- mshowPersonA
    return ("(" ++ n ++ "," ++ a ++ ")" )
    
{-
runReader mshowPersonN  $ Person "ada" 20
"NAME:ada"
runReader mshowPersonA  $ Person "ada" 20
"AGE:20"
runReader mshowPerson  $ Person "ada" 20
"(NAME:ada,AGE:20)"
-}