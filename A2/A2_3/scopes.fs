let rec bizarre b q =
    let mango z = b
    in
        if b then ( bizarre false mango )
            else ( mango 17 , q 17 );;

let dummy = function x -> false
let bongo = bizarre true dummy;;

printfn "%A value for bongo" (bongo)
