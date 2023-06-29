-- -- -- Laborator 10 PF -- -- --
    -- Functori aplicativi --



{- 
class Functor f where 
     fmap :: (a -> b) -> f a -> f b 
class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b

Just length <*> Just "world"

Just (++" world") <*> Just "hello,"     -- hello,world
pure (+) <*> Just 3 <*> Just 5          -- Just 8
pure (+) <*> Just 3 <*> Nothing         -- Nothing
                                
(++) <$> ["ha","heh"] <*> ["?","!"]

-}


-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- ex. 1:

-- [a]:=[]|a:[a]     => [1,2] == 1:2:[] == (:) 1 ((:)2 [])

data List a = Nil
            | Cons a (List a)
        deriving (Eq, Show)

instance Functor List where
    fmap f (Cons a as)= Cons (f a) (fmap f as) 
    fmap f Nil = Nil 



app::List a -> List a -> List a
app Nil l = l
app (Cons a as) l = Cons a (app as l)

instance Applicative List where
    pure a = Cons a Nil 
--pure 1 :: [Int]==[1]==1:[]
--fmap h l2 'app' t <*> l2 -> h=head, t=tail (din l1) , l2

--folosim functia app
    Nil <*> l2 = Nil
    (Cons h t) <*> l2 = (fmap h l2) `app` (t <*>  l2)



f = Cons (+1) (Cons (*2) Nil)
v = Cons 1 (Cons 2 Nil)
test1 = (f <*> v) == Cons 2 (Cons 3 (Cons 2 (Cons 4 Nil)))


-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- ex. 2:

data Cow = Cow {
        name :: String
        , age :: Int
        , weight :: Int
        } deriving (Eq, Show)

    -- a)
noEmpty :: String -> Maybe String
noEmpty s = Just s
--noEmpty "" = Nothing

noNegative :: Int -> Maybe Int
noNegative a 
    | a>=0  = Just a
    | otherwise = Nothing

test21 = noEmpty "abc" == Just "abc"
test22 = noNegative (-5) == Nothing 
test23 = noNegative 5 == Just 5 

    -- b)
cowFromString :: String -> Int -> Int -> Maybe Cow
cowFromString n a w 
    | noEmpty n == Nothing = Nothing
    | noNegative a == Nothing = Nothing
    | noNegative w == Nothing = Nothing
    | otherwise =  pure(Cow {name=n,age=a,weight=w})


test24 = cowFromString "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})
    -- c) Cow::String -> (Int->Int->Cow)
cFS :: String -> Int -> Int -> Maybe Cow
cFS n a w = fmap Cow (noEmpty n) <*> noNegative a <*> noNegative w 

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- ex. 3:

newtype Name = Name String deriving (Eq, Show)
newtype Address = Address String deriving (Eq, Show)

data Person = Person Name Address
    deriving (Eq, Show)
    -- a)
validateLength :: Int -> String -> Maybe String
validateLength x l 
    | (length l) > x = Nothing
    | otherwise = Just l

test31 = validateLength 5 "abc" == Just "abc"

    -- b)
mkName :: String -> Maybe Name
mkName s
    | validateLength 25 s==Just s  = Just (Name s)
    | otherwise = Nothing 

mkAddress :: String -> Maybe Address
mkAddress s
    | validateLength 100 s==Just s = Just (Address s)
    | otherwise = Nothing

test32 = mkName "Gigel" ==  Just (Name "Gigel")
test33 = mkAddress "Str Academiei" ==  Just (Address "Str Academiei")

    -- c)
mkPerson :: String -> String -> Maybe Person
mkPerson n a
    | mkAddress n== Nothing  =Nothing
    | mkAddress a==Nothing =Nothing
    | otherwise =Just(Person (Name n) (Address a))

test34 = mkPerson "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))

    -- d)
mkP :: String -> String -> Maybe Person  --echivalentul functiei mkPerson
mkP n a = fmap Person (mkName n) <*> (mkAddress a)

mkN :: String -> Maybe Name     
mkN n = fmap Name(validateLength 25 n)

mkA :: String -> Maybe Name
mkA a = fmap Name(validateLength 100 a)