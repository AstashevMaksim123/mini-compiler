#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build"
TMP_DIR="$BUILD_DIR/test_artifacts"
POS_DIR="$ROOT_DIR/tests/positive"
NEG_DIR="$ROOT_DIR/tests/negative"
SHOWCASE_DIR="$ROOT_DIR/tests/showcase"
SHOWCASE_ASM_DIR="$BUILD_DIR/showcase_asm"

mkdir -p "$BUILD_DIR" "$TMP_DIR" "$SHOWCASE_ASM_DIR"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR"
cmake --build "$BUILD_DIR" -j2

pass_count=0
fail_count=0

run_positive() {
    local src="$1"
    local base
    base="$(basename "$src" .mc)"
    local obj="$TMP_DIR/$base.o"
    local exe="$TMP_DIR/$base.exe"
    local log="$TMP_DIR/$base.log"
    local expected
    expected="$(tr -d '\r' < "$POS_DIR/$base.expected")"

    if ! "$BUILD_DIR/mini_cc" "$src" --emit-ir -o "$obj" >"$log" 2>&1; then
        echo "[FAIL] $base: compiler failed"
        cat "$log"
        fail_count=$((fail_count + 1))
        return
    fi

    if ! llvm-nm "$obj" | grep -q " compiled_fn$"; then
        echo "[FAIL] $base: symbol compiled_fn not exported"
        fail_count=$((fail_count + 1))
        return
    fi

    if ! clang "$ROOT_DIR/runtime/main.c" "$obj" -o "$exe" >"$log" 2>&1; then
        echo "[FAIL] $base: linker failed"
        cat "$log"
        fail_count=$((fail_count + 1))
        return
    fi

    local output
    output="$("$exe")"
    if [[ "$output" != "$expected" ]]; then
        echo "[FAIL] $base: expected '$expected', got '$output'"
        fail_count=$((fail_count + 1))
        return
    fi

    echo "[PASS] $base"
    pass_count=$((pass_count + 1))
}

run_negative() {
    local src="$1"
    local base
    base="$(basename "$src" .mc)"
    local obj="$TMP_DIR/$base.o"
    local log="$TMP_DIR/$base.log"
    local expected
    expected="$(tr -d '\r' < "$NEG_DIR/$base.error")"

    if "$BUILD_DIR/mini_cc" "$src" -o "$obj" >"$log" 2>&1; then
        echo "[FAIL] $base: compiler unexpectedly succeeded"
        fail_count=$((fail_count + 1))
        return
    fi

    if ! grep -Fq "$expected" "$log"; then
        echo "[FAIL] $base: expected diagnostic '$expected'"
        cat "$log"
        fail_count=$((fail_count + 1))
        return
    fi

    echo "[PASS] $base"
    pass_count=$((pass_count + 1))
}

run_showcase() {
    local src="$1"
    local base
    base="$(basename "$src" .mc)"
    local obj="$TMP_DIR/$base.o"
    local exe="$TMP_DIR/$base.exe"
    local ll="$TMP_DIR/$base.ll"
    local asm="$SHOWCASE_ASM_DIR/$base.s"
    local log="$TMP_DIR/$base.log"
    local expected
    expected="$(tr -d '\r' < "$SHOWCASE_DIR/$base.expected")"

    if ! "$BUILD_DIR/mini_cc" "$src" --emit-ir -o "$obj" >"$log" 2>&1; then
        echo "[FAIL] $base: compiler failed"
        cat "$log"
        fail_count=$((fail_count + 1))
        return
    fi

    if ! clang -S "$ll" -o "$asm" >"$log" 2>&1; then
        echo "[FAIL] $base: assembly generation failed"
        cat "$log"
        fail_count=$((fail_count + 1))
        return
    fi

    if ! clang "$ROOT_DIR/runtime/main.c" "$obj" -o "$exe" >"$log" 2>&1; then
        echo "[FAIL] $base: linker failed"
        cat "$log"
        fail_count=$((fail_count + 1))
        return
    fi

    local output
    output="$("$exe")"
    if [[ "$output" != "$expected" ]]; then
        echo "[FAIL] $base: expected '$expected', got '$output'"
        fail_count=$((fail_count + 1))
        return
    fi

    echo "[PASS] $base (showcase)"
    pass_count=$((pass_count + 1))
}

for src in "$POS_DIR"/*.mc; do
    run_positive "$src"
done

for src in "$NEG_DIR"/*.mc; do
    run_negative "$src"
done

for src in "$SHOWCASE_DIR"/*.mc; do
    run_showcase "$src"
done

echo "Passed: $pass_count"
echo "Failed: $fail_count"

if [[ "$fail_count" -ne 0 ]]; then
    exit 1
fi
