-- -- -- Laborator 7 PF -- -- --
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- 1. Expresii si arbori


data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)


-- ex. 1.1
instance Show Expr where
    show::Expr->String
    show (Const a) = show a
    show ( e1 :+: e2 ) = "(" ++ show e1 ++ "+" ++ show e2 ++ ")"
    show ( e1 :*: e2 ) = "(" ++ show e1 ++ "*" ++ show e2 ++ ")"


-- ex. 1.2
evalExp :: Expr -> Int
evalExp (Const c)=c
evalExp (e1 :+: e2) = evalExp e1 + evalExp e2 
evalExp (e1 :*: e2) = evalExp e1 * evalExp e2 


    -- teste 
exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

-- ex. 1.3
evalArb :: Tree -> Int
evalArb (Lf a) = a
evalArb (Node Add n1 n2) = evalArb n1 + evalArb n2
evalArb (Node Mult n1 n2) = evalArb n1 * evalArb n2


    -- teste
arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

-- ex 1.4
expToArb :: Expr -> Tree
expToArb (Const c) = Lf c
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2) 
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)


-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
-- 2. Clasa Collection

-- ex.2.1

class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
      :: Ord key
      => key -> value -> c key value -> c key value
  clookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  -- 
  keys = map fst . toList
  
  values :: c key value -> [value]
  --
  values = map snd . toList
  

  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  fromList [] = empty
  -- 
  fromList (x:xs)= insert (fst x) (snd x) (fromList xs)

-- ex. 2.2
newtype PairList k v
  = PairList { getPairList :: [(k, v)] }

instance Collection PairList where
    empty :: PairList key value 
    empty = PairList []

    toList::PairList key value -> [(key,value)]
    toList = getPairList

    singleton::key->value-> PairList key value
    singleton k v = PairList [(k,v)]

    insert :: (Eq key) => key -> value -> PairList key value -> PairList key value
    insert k v (PairList l) = PairList$ (k,v):filter((/=k).fst) l

    clookup :: Ord key => key -> PairList key value -> Maybe value
    clookup k (PairList l) = lookup k l

    delete :: Ord key => key -> PairList key value -> PairList key value
    delete k (PairList l) = PairList$ filter((/=k).fst) l




    
data SearchTree key value
  = Empty
  | BNode
      (SearchTree key value) -- elemente cu cheia mai mica
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare