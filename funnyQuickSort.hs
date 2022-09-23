{-
Author: ScierKnave (Dereck Piche)
Language: Haskell
Description:
This is a ridiculous implementation of quickSort 
that I made purely to confuse myself
-}


quickSort :: [Int] -> [Int]
quickSort list =
    if length list <= 1
        then list
    else
        let
            left = tail ( fst (pivoting (head list) list) )
            pivot = head ( fst (pivoting (head list) list) )
            right = snd (pivoting (head list) list) 
        in 
            (quickSort left) ++ [pivot] ++ (quickSort right)



--returns list of all elements bigger or equal to a pivot in argument list
pivoting :: Int -> [Int] -> ([Int],[Int])
pivoting pivot list =
    if length list == 0
        then ([],[])
    --put list[p1] in smaller than or equal to pivot list and increment p1
    else if head list <= pivot
        then 
            (
                [head list] ++ fst (pivoting pivot (tail list))
                ,
                snd (pivoting pivot (tail list))
            )
    --put list[p2] in bigger than pivot list and decrement p2
    else if last list > pivot
        then 
            (
                fst (pivoting pivot (init list))
                ,
                snd (pivoting pivot (init list)) ++ [last list]
            )
    --put list[p1] in smaller than or equal to pivot list and increment p1
    --put list[p2] in bigger than pivot list and decrement p2
    else 
            (
                [last list] ++ fst (pivoting pivot (init (tail list)))
                ,
                snd (pivoting pivot (init (tail list))) ++ [head list] 
            )





