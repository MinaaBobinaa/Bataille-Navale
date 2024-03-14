prog=bataille_navale
setup() {
  load 'bats/test/test_helper/bats-support/load'
  load 'bats/test/test_helper/bats-assert/load'
}

@test "Test 1" {
    run ./$prog ""
}
