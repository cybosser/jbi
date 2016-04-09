#include <gtest/gtest.h>

#include <jbi/core/exceptions.h>

TEST(core_exceptions_test, throw_test)
{
    class dummy_exception : public std::exception { };

    EXPECT_THROW(JBI_THROW(dummy_exception()), dummy_exception);
}
