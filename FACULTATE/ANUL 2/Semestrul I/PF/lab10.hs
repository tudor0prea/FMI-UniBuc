-- -- -- Laborator 10 PF -- -- --
          -- Functor --

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- Scrieti instante ale clasei Functor pentru tipurile:


    {-
    class Functor f where
    fmap : : ( a -> b ) -> f a -> f b
    -}

newtype Identity a = Identity a
instance Functor Identity where
    fmap::(a->b)->Identity a -> Identity b
    fmap f (Identity a) = Identity (f a)


data Pair a = Pair a a
instance Functor Pair where
    fmap::(a->b)->Pair a -> Pair b
    fmap f (Pair a b)= Pair (f a) (f b)


data Constant a b = Constant b  -- a se numeste tip fantoma
-- Constant 'x' :: Constant Int Char
-- Constant 'x' :: Constant Bool Char
instance Functor (Constant a) where
    fmap f (Constant b) = Constant (f b)

data Two a b = Two a b      --b este cel mai in dreapta, deci el se modifica
instance Functor (Two a) where
    fmap f (Two a b)= Two a (f b)

data Three a b c = Three a b c
instance Functor (Three a b) where
    fmap f (Three a b c)= Three a b (f c)

data Three' a b = Three' a b b
instance Functor (Three' a) where
    fmap f(Three' a b b1)= Three' a (f b) (f b1) 

data Four a b c d = Four a b c d
instance Functor (Four a b c) where
    fmap f(Four a b c d) = Four a b c (f d)



data Four'' a b = Four'' a a a b
instance Functor (Four'' a) where
    fmap f(Four'' a a1 a2 b) = Four'' a a1 a2 (f b)

data Quant a b = Finance | Desk a | Bloor b
instance Functor (Quant a) where
    fmap f Finance = Finance
    fmap f(Desk a) = Desk a
    fmap f(Bloor b) = Bloor (f b)

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- S-ar putea să fie nevoie să adăugati unele constrângeri 
-- la definirea instantelor

data LiftItOut f a = LiftItOut (f a) -- f este tip de data
instance Functor f=>Functor (LiftItOut f) where
    fmap aTOb (LiftItOut fA) = LiftItOut(fmap aTOb fA)

data Parappa f g a = DaWrappa (f a) (g a)
instance (Functor f, Functor g)=>Functor (Parappa f g) where
    fmap fA (DaWrappa p1 p2) = DaWrappa (fmap fA p1) (fmap fA p2)

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
instance Functor g => Functor (IgnoreOne f g a) where
    fmap fA (IgnoringSomething p1 p2) = IgnoringSomething p1 (fmap fA p2)


data Notorious g o a t = Notorious (g o) (g a) (g t)
instance (Functor g) => Functor (Notorious g o a) where
    fmap fA (Notorious o a t)= Notorious o a (fmap fA t)

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
instance Functor GoatLord where
    fmap fA NoGoat= NoGoat
    fmap fA (OneGoat a) = OneGoat (fA a)
    fmap fA (MoreGoats a b c) = MoreGoats (fmap fA a)  (fmap fA b)  (fmap fA c)

data TalkToMe a = Halt | Print String a | Read (String -> a)
instance Functor TalkToMe where
    fmap fA Halt = Halt
    fmap fA (Print s x) = Print s (fA x)
    fmap fA (Read x) = Read (fmap fA x)