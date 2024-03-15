prog=bataille_navale
setup() {
  load 'bats/bats-support/load'
  load 'bats/bats-assert/load'
}

@test "Test 1" {
    run ./$prog ""
}
