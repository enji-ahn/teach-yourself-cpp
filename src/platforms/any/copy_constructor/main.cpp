#include <iostream>

struct NoImplicitCopy {
	NoImplicitCopy() = default;
	explicit NoImplicitCopy(NoImplicitCopy&) = default;
};

NoImplicitCopy foo()
{
	NoImplicitCopy n;
	return n;
}

void bar(NoImplicitCopy n)
{ }

int main(void)
{
	NoImplicitCopy  n;
	NoImplicitCopy x(n);

	n = foo();
	bar(n);

    return EXIT_SUCCESS;
}
