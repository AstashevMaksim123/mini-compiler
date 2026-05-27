fn compiled_fn(arg: int) -> int {
    let x: int = arg;
    {
        let x: int = 3;
        {
            let y: int = x + 4;
            if y == 7 {
                return x + y;
            } else {
                return 0;
            }
        }
    }
}

