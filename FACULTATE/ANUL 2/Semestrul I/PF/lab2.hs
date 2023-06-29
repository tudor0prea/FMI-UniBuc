-- -- -- Laboratorul 2 PF -- -- --

-- ! even = verificare par/impar
-- -- Exercitii -- --
-- ex. 1
poly2 :: Double -> Double -> Double -> Double -> Double 
poly2 a b c n = a*n*n+b*n+c

-- ex. 2
eeny :: Integer -> String
eeny x = if even x == True
    then "eeny"
    else "meeny" 

-- ex. 3
fizzbuzz :: Integer -> String
fizzbuzz x = if mod x 3 == 0 && mod x 5 == 0
    then "FizzBuzz"
    else if mod x 3 == 0
        then "Fizz"
        else if mod x 5 == 0
            then "Buzz"
            else " "
    
-- -- Recursivitate -- --     
fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)

-- ex. 4
tribonacci :: Integer -> Integer
tribonacci 1 = 1
tribonacci 2 = 1
tribonacci 3 = 2
tribonacci x = tribonacci (x-1) + tribonacci (x-2) + tribonacci(x-3)
--          + de adaugat prin cazuri

-- ex. 5
binomial :: Integer -> Integer -> Integer
binomial n 0 = 1
binomial 0 k = 0
binomial n k = binomial (n-1) k + binomial (n-1)(k-1)

-- ex. 6
    -- a)
verifL :: [Int] -> Bool
verifL l  
    | even (length(l)) = True  
    | otherwise = False

    -- b)
takefinal :: [Int] -> Int -> [Int]
takefinal l n = if(length l) > n 
    then drop (length l - n) l
    else l

    -- c)       
remove :: [a] -> Int -> [a]
remove l n = take n l ++ drop (n+1) l
      
                -- avem ++ pt concat listelor
                -- take si drop 


-- -- Recursivitate pe Liste -- --
sumImp :: [Int] -> Int
sumImp l 
    | length l>0 = mod (head l) 2*(head l) + suma
    | otherwise = 0
    where suma=sumImp (tail l)

-- sau:
-- sumImp[] =0
-- sumImp(x:xs)
-- |even x = sumImp(xs)
-- |otherwise = s+ sumImp(xs)




-- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
 | even h    = h `div` 2 : t'
 | otherwise = t'
 where t' = semiPareRec t

totalLen :: [String] -> Int
totalLen [] = 0
totalLen(x:xs) 
    | length(x)==0 = totalLen(xs)
    | head x == 'A' = length (x) + totalLen xs
    | otherwise = totalLen(xs)