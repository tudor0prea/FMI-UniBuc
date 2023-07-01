module Program where
import Exp
import Lab2 ( Parser, endOfInput, whiteSpace, reserved, semiSep1 )
import Parsing ( expr, var, parseFirst )
import Sugar ( desugarExp, desugarVar )
import Eval ( substitute )

import Control.Applicative ( Alternative(..) )
import System.IO ( stderr, hPutStrLn )
import qualified Data.Map.Strict as Map

data Definition = Definition
  { defHead :: Var
  , defArgs :: [Var]
  , defBody :: ComplexExp
  }
  deriving (Show)

definition :: Parser Definition
definition
  = undefined

-- >>> parseFirst definition "id := \\x -> x"
-- Just (Definition {defHead = Var {getVar = "id"}, defArgs = [], defBody = CLam (Var {getVar = "x"}) (CX (Var {getVar = "x"}))})

-- >>> parseFirst definition "id x := x"
-- Just (Definition {defHead = Var {getVar = "id"}, defArgs = [Var {getVar = "x"}], defBody = CX (Var {getVar = "x"})})

-- >>> parseFirst definition "const x y := x"
-- Just (Definition {defHead = Var {getVar = "const"}, defArgs = [Var {getVar = "x"},Var {getVar = "y"}], defBody = CX (Var {getVar = "x"})})

--Applicative pune la dispoziție și doi operatori derivați, [`*>`](https://hackage.haskell.org/package/base-4.17.0.0/docs/Prelude.html#v:-42--62-) și [`<*`](https://hackage.haskell.org/package/base-4.17.0.0/docs/Prelude.html#v:-60--42-), care permit ignorarea valorii unei computații:

--- | succes doar dacă am șirul de intrare este vid 
--endOfInput :: Parser ()
--endOfInput  = Parser go
--  where
--    go "" = [((), "")]
--    go _ = []

--De asemeni, putem folosi `<*` înpreună cu `endOfInput` pentru a garanta că tot șirul de intrare a fost consumat:

--```{.hs .solve .test}
-- | endOfInput
-- >>> apply (digit <* endOfInput) "123"
-- []
-- >>> apply (digit <* endOfInput) "1"
-- [('1',"")]


program :: Parser [Definition]
program = undefined

-- >>> parseFirst program "    id x := x ; const x y := x"
-- Nothing

-- >>> parseFirst program "    id x := x ; const x y := x ;"
-- Just [Definition {defHead = Var {getVar = "id"}, defArgs = [Var {getVar = "x"}], defBody = CX (Var {getVar = "x"})},Definition {defHead = Var {getVar = "const"}, defArgs = [Var {getVar = "x"},Var {getVar = "y"}], defBody = CX (Var {getVar = "x"})}]


type Environment = Map.Map IndexedVar Exp

definitionExp :: Definition -> ComplexExp
definitionExp def = undefined

-- >>> definitionExp (Definition {defHead = Var {getVar = "const"}, defArgs = [Var {getVar = "x"},Var {getVar = "y"}], defBody = CX (Var {getVar = "x"})})
-- CLam (Var {getVar = "x"}) (CLam (Var {getVar = "y"}) (CX (Var {getVar = "x"})))

-- desugarVar :: Var -> IndexedVar
-- desugarVar = makeIndexedVar . getVar

-- >>> desugarVar (Var "x")
-- IndexedVar {ivName = "x", ivCount = 0}

programEnv :: [Definition] -> Environment
programEnv pgm = undefined

normalizeEnv :: Environment -> Exp -> Exp
normalizeEnv env e = maybe e (normalizeEnv env) (step e)
  where
    step (X x) = Map.lookup x env
    step (Lam x e) = Lam x <$> step e
    step (App (Lam x ex) e) = Just (substitute x e ex)
    step (App e1 e2)
      = case step e1 of
        Nothing -> App e1 <$> step e2
        Just e1' -> Just (App e1' e2)
