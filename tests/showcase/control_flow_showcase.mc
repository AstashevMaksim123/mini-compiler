fn score(x: int) -> int {
    if x % 2 == 0 {
        return x + 1;
    } else {
        return x * 2;
    }
}

fn compiled_fn(arg: int) -> int {
    let mut total: int = 0;

    for let mut i: int = 0; i < arg; i = i + 1 {
        if i == 2 {
            continue;
        } else {
            total = total + 0;
        }

        switch i % 4 {
            case 0 {
                total = total + score(i);
            }
            case 1 {
                total = total + 10;
            }
            case 2 {
                total = total + 20;
            }
            default {
                total = total + 30;
            }
        }

        if total > 60 {
            break;
        } else {
            total = total + 1;
        }
    }

    return total;
}

