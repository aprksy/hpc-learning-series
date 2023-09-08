package tests

import (
	"learn-go/tdd/somepkg"
	"testing"
)

func TestSum(t *testing.T, c somepkg.Calculator) {
	expect := 3
	actual := c.Sum(1, 2)
	if actual != expect {
		t.Errorf("expected to get %d, but getting %d instead", expect, actual)
	}
}

func TestMain(m *testing.M) {
	calc := somepkg.DefaultCalculator{}
	TestSum(&testing.T{}, calc)
}
