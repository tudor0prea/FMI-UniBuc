import Distribution.SPDX (LicenseId(AFL_1_2))
-- -- -- Laborator 12 PF -- -- --
    -- Exercitii pentru Foldable --


-- ex 1
import Data.Monoid


elem1 :: (Foldable t, Eq a) => a -> t a -> Bool --valoare, lista
elem1 v l = foldr ( \x y -> x==v  || y ) False l

null1 :: (Foldable t) => t a -> Bool
null1 l = foldr ( \x y-> False) True l   --x,y sunt elem curent si ce a fost

length1 :: (Foldable t) => t a -> Int
length1 l= foldr ( \_ y-> y+1 ) 0 l  -- y e "acumulatorul"

toList1 :: (Foldable t) => t a -> [a]
toList1 = foldr (\x y -> x:y) [] 
    -- toList1 = foldr (:) []

fold1 :: (Foldable t, Monoid m) => t m -> m -- asoc + el neutru
fold1 = foldMap(id)
     -- Hint: folosiți foldMap

data Constant a b = Constant b

instance Foldable (Constant a) where
    foldMap f (Constant b) = f b

data Two a b = Two a b
instance Foldable (Two a) where
    foldMap f (Two a b) = f b 

data Three a b c = Three a b c

data Three' a b = Three' a b b
instance Foldable (Three' a) where
    foldMap f (Three' a b1 b2) = f b1 `mappend` f b2 

data Four' a b = Four' a b b b

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)