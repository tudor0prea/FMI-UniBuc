x = let x=3; y = 4 in x * y;

data Fish = G | B | S

--f xs = foldr (&&) True [x `mod` 3 | x<-xs]

hof::(a->b->c) -> (a->b) ->a->c 
hof h f a = undefined

f x y= if x>y then x*x else x+x
--drop 2 [(x,y) | x<-[1..4], y<-['a'..'z'], y `in` "aeiou"]

f::Integral a=>a->a->a

l1=['a'..]
l2=[1..3]
a = take 100 $  foldl (flip (:)) [] [1..]
