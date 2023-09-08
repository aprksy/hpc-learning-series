package somepkg

type Calculator interface {
	Sum(a int, b int) int
}

type DefaultCalculator struct{}

func (d DefaultCalculator) Sum(a int, b int) int {
	return a + b
}
