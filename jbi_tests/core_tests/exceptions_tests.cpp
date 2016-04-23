#include <gtest/gtest.h>

#include <jbi/core/exceptions.h>

class dummy_exception : public std::exception
{ };

TEST(exceptions_test, throw_test)
{
    EXPECT_THROW(JBI_THROW(dummy_exception()), dummy_exception);
}

TEST(exceptions_test, throw_if_test)
{
    EXPECT_THROW(JBI_THROW_IF(1 == 1, dummy_exception()), dummy_exception);
    EXPECT_NO_THROW(JBI_THROW_IF(1 != 1, dummy_exception()));
}
