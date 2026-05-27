fn compiled_fn(arg: int) -> int {
    let x: int = arg + 5;
    switch x {
        case 0 {
            return 100;
        }
        case 1 {
            return 101;
        }
        default {
            return x;
        }
    }
}

