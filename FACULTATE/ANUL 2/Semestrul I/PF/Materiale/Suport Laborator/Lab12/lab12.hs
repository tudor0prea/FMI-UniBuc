import Data.Monoid


elem1 :: (Foldable t, Eq a) => a -> t a -> Bool
elem1 = undefined

null1 :: (Foldable t) => t a -> Bool
null1 = undefined

length1 :: (Foldable t) => t a -> Int
length1 = undefined

toList1 :: (Foldable t) => t a -> [a]
toList1 = undefined

fold1 :: (Foldable t, Monoid m) => t m -> m
fold1 = undefined -- Hint: folosiți foldMap

data Constant a b = Constant b

data Two a b = Two a b

data Three a b c = Three a b c

data Three' a b = Three' a b b

data Four' a b = Four' a b b b

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
