import Data.Char
-- -- -- Laboratorul 3 PF -- -- --

-- ex. 1

esteVocala :: Char -> Bool
esteVocala c = elem c "aeiou";

nrVocale :: [Char] -> Int
nrVocale [] = 0;
nrVocale (x:xs)
    | esteVocala(x) == True =1+nrVocale(xs)
    | otherwise = nrVocale(xs);


nrVocalePalindrom :: [String] -> Int
nrVocalePalindrom[]=0
nrVocalePalindrom(x:xs)
    | x == reverse (x)  = nrVocale(x) + nrVocalePalindrom(xs)
    | otherwise= nrVocalePalindrom(xs)

-- ex. 2

f :: Int -> [Int] -> [Int]
f n[]=[]
f n(x:xs)
    | even x=x:n:f n xs
    | otherwise = x:f n xs

-- ex. 3
divizori :: Int -> [Int]
divizori x= [y | y<-[1..x], x `mod` y==0]

-- ex. 4
listadiv :: [Int] -> [[Int]]
listadiv lista=[divizori element | element<-lista]


-- ex. 5
inIntervalComp:: Int -> Int -> [Int] -> [Int]
inIntervalComp x y l =[ a | a<-l, a>=x, a<=y ]

inIntervalRec:: Int -> Int -> [Int] -> [Int]
inIntervalRec a b []=[]
inIntervalRec a b (x:xs)
    | x>=a && x<=b = x : inIntervalRec a b xs
    | otherwise = inIntervalRec a b xs

-- ex. 6
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (x:xs)
    |  x> 0  = 1 + pozitiveRec(xs)
    | otherwise = pozitiveRec(xs)

pozitiveComp::[Int] -> Int
pozitiveComp lista = length([x | x<-lista, x>0]);

-- ex. 7
    --a)
poz:: Int-> [Int]->[Int]
poz p [] = []
poz p (x:xs)
    | odd x  = p: poz(p+1) xs   -- impar
    | otherwise = poz(p+1) xs



pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec n = poz 0 n; 

    --b)
pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp lista = [element | (element, index) <- zip [0..] lista, odd index]

    --a) cu o singura functie
pozitiiImpareRec1 :: [Int] -> Int -> [Int]
pozitiiImpareRec1 [] index = []
pozitiiImpareRec1 (x:xs) index
    | not . even $ index = x : pozitiiImpareRec1 xs (index+1)
    | otherwise = pozitiiImpareRec1 xs (index+1)

-- ex. 8
    --b)

    -- importam sus, in fisier: import Data.Char

multiDigits:: [Char] -> Int
multiDigits sir = product[digitToInt elem | elem<-sir, isDigit elem==True];