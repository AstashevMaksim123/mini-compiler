fn helper(x: int) -> int {
    return x * 2;
}

fn compiled_fn(arg: int) -> int {
    return helper(arg) + 1;
}

