{-
Author: ScierKnave (Dereck Piche)
Language: Haskell
Description:
This is an implementation of integer quickSort 
that works only on lists without doubles
-}
quickSort :: [Int] -> [Int]
quickSort list =
    if length list <= 1
        then list
    else
        let
            pivot = head list --get first element of the list
            -- get list of elements smaller than the pivot
            smList = getLesserThan pivot list
            -- get list of elements bigger than the pivot
            biList = map negate ( getLesserThan (negate pivot) (map negate list) )
        in 
            (quickSort smList) ++ [pivot] ++ (quickSort biList)


--returns list of all elements bigger or equal to a pivot in argument list
getLesserThan :: Int -> [Int] -> [Int]
getLesserThan pivot list =
    if length list == 0
        then list
    else if (head list) < pivot
        then [head list] ++ getLesserThan pivot (tail list)
    else getLesserThan pivot (tail list)
    




