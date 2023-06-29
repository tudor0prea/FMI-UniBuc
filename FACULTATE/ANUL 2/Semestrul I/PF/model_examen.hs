-- -- -- Model examen PF -- -- --
         -- 19.01.2023 --


-- Subiectul I [ADT+Clase]

data Point = Pt[Int]
            deriving Show

data Arb = Empty | Node Int Arb Arb
          deriving Show 

class ToFromArb a where
    toArb::a->Arb
    toArb2::a->Arb
    fromArb::Arb->a  

inserare :: Int -> Arb -> Arb
inserare n Empty = Node n Empty Empty
inserare n (Node x l r)  
    | n<x = Node x (inserare n l) r
    | otherwise = Node x l (inserare n r)

instance ToFromArb Point where
    -- flip schimba ordinea parametrilor
    toArb (Pt a) = foldl (flip inserare) Empty a 

    fromArb Empty = Pt []
    fromArb (Node n l r) = Pt (n : soll ++ solr)
        where 
            Pt soll=fromArb l 
            Pt solr=fromArb r

    toArb2 (Pt a)= foldr inserare Empty (reverse a) 


-- Subiectul II [Liste+Monade]

-- 2 variante fara monade (comprehensiune pe liste si cazuri)   
getFromInterval :: Ord a => a -> a -> [a] -> [a]
getFromInterval a b l = [ x | x<-l,  x>=a, x<=b]

getFromInterval3 :: Ord t => t -> t -> [t] -> [t]
getFromInterval3 a b [] = []
getFromInterval3 a b (x:xs) 
    | x>=a && x<=b  = x: getFromInterval3 a b xs
    | otherwise = getFromInterval3 a b xs

-- 1 varianta cu monade
getFromInterval2 :: Ord b => b -> b -> [b] -> [b]
getFromInterval2 a b l = do
    x<-l
    if(x>=a && x<=b) then [x] 
    else []
        --pentru fiecare valoare din lista, produce o noua lista si apoi
        --le concateneaza

-- Subiectul III [Monade]

newtype ReaderWriter env a = RW {getRW :: env-> (a,String)}

instance Monad (ReaderWriter env) where
    return :: a -> ReaderWriter env a
    return x = RW( \_ -> (x,""))

    (>>=) :: ReaderWriter env a-> (a -> ReaderWriter env b) -> ReaderWriter env b
    ma >>= k = RW f 
        where f env = let (a, st) = getRW ma env 
                          (b, st2) = getRW (k a) env
                       in (b, st++st2)    
 ------


instance Applicative (ReaderWriter env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance Functor (ReaderWriter env) where              
  fmap f ma = pure f <*> ma    

-- newtype Reader env a = Reader { runReader :: env -> a }


-- instance Monad (Reader env) where
--   return x = Reader (\_ -> x)
--   (>>=) :: Reader env a -> (a -> Reader env b) -> Reader env b
--   ma >>= k = Reader f
--     where f env = let a = runReader ma env
--                   in  runReader (k a) env


-- newtype WriterS a = Writer { runWriter :: (a, String) } 


-- instance  Monad WriterS where
--   return :: a -> WriterS a
--   return va = Writer (va, "")
--   (>>=) :: WriterS a -> (a -> WriterS b) -> WriterS b
--   ma >>= k = let (va, log1) = runWriter ma
--                  (vb, log2) = runWriter (k va)
--              in  Writer (vb, log1 ++ log2)

