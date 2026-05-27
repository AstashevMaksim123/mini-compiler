fn compiled_fn(arg: int) -> int {
    let mut total: int = 0;
    for let mut i: int = 0; i < 5; i = i + 1 {
        switch i % 3 {
            case 0 {
                total = total + 10;
            }
            case 1 {
                total = total + 1;
            }
            default {
                total = total + 100;
            }
        }
    }
    return total;
}

