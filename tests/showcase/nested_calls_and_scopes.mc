fn clamp(x: int) -> int {
    switch x {
        case 0 {
            return 0;
        }
        case 1 {
            return 1;
        }
        default {
            if x > 5 {
                return 5;
            } else {
                return x;
            }
        }
    }
}

fn mix(a: int, b: int) -> int {
    let mut result: int = a;

    {
        let inner: int = b + 2;
        if inner > 10 {
            return clamp(inner);
        } else {
            result = result + inner;
        }
    }

    return clamp(result);
}

fn compiled_fn(arg: int) -> int {
    let left: int = mix(arg, 3);
    let right: int = mix(2, arg / 2);

    if (left == 5) && (right == 5) {
        return left + right;
    } else {
        return 0;
    }
}

