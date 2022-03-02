let rec bizarre b q =
    let mango z = b
    in
        if b then ( bizarre false mango )
            else ( mango 17 , q 17 );;

printfn "%A value for bizarre" (bizarre)

let dummy = function x -> false
let bongo = bizarre true dummy;;

printfn "%A value for dummy" (dummy)
printfn "%A value for bongo" (bongo)