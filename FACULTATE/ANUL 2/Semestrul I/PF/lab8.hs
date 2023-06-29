-- -- -- Laborator 8 PF -- -- --
    -- ADT. Clase de Tipuri --

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- Exercitiul 1


data Punct = Pt [Int]

data Arb = Vid | F Int | N Arb Arb
          deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a
    
    -- a)

-- nu merge varianta asta

-- f::Int->String
-- f 1="(";
-- f _="";

-- nr=0;
-- instance Show Punct where
--     show::Punct->String
--     show (Pt []) = "()";
--     show (Pt (x:[])) = show x;
--     show (Pt (x:xs)) = (f (nr)) ++ show x ++ " , " ++ show (Pt xs) ++ ")";


instance Show Punct where 
    show(Pt l)="("++ parse l ++ ")"
        where
            parse[]=" ";
            parse[x]=show x;
            parse(x:xs)=show x ++ " , " ++ parse xs; 
-- Pt [1,2,3]
-- (1, 2, 3)


   
    -- b)

instance ToFromArb Punct where
    toArb::Punct->Arb;
    toArb (Pt []) = Vid;
    toArb (Pt (x:xs)) = N(F x) (toArb(Pt xs)) 

    fromArb::Arb->Punct
    fromArb Vid = Pt []
    fromArb (F x) = Pt[x]
    fromArb (N stg dr) = Pt (l1 ++ l2)
        where 
            Pt l1 = fromArb stg
            Pt l2 = fromArb dr

-- Pt []
-- ()

-- toArb (Pt [1,2,3])
-- N (F 1) (N (F 2) (N (F 3) Vid))
-- fromArb $ N (F 1) (N (F 2) (N (F 3) Vid)) :: Punct
--  (1,2,3)



-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- Exercitiul 2
data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
  perimeter :: (Floating a) => g a -> a
  area :: (Floating a) =>  g a -> a


    -- a)

instance GeoOps Geo where
    perimeter (Square a) = 4*a
    perimeter (Rectangle a b) = 2*(a+b)
    perimeter (Circle a) = 2*pi*a

    area (Square a) = a*a
    area (Rectangle a b) = a*b
    area (Circle a) = pi*a*a

    --b)
instance (Floating a, Eq a)=>Eq (Geo a)  where
    (==) :: (Floating a, Eq a) => Geo a -> Geo a -> Bool
    a==b =   perimeter a == perimeter b 



-- ghci> pi
-- 3.141592653589793