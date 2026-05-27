fn classify(x: int) -> int {
    switch x % 3 {
        case 0 {
            return 3;
        }
        case 1 {
            return 5;
        }
        default {
            return 7;
        }
    }
}

fn compiled_fn(arg: int) -> int {
    let mut sum: int = 0;

    for let mut i: int = 0; i < arg; i = i + 1 {
        let value: int = classify(i);

        {
            let mut local: int = value;
            if (i > 0) && (i < 4) {
                local = local + i;
            } else {
                local = local - 1;
            }
            sum = sum + local;
        }

        if sum > 40 {
            break;
        } else {
            continue;
        }
    }

    return sum;
}

