#include <gmock/gmock.h>

#include <jbi/core/string.h>

TEST(to_sting_tests, types_without_to_string_method_test)
{

    EXPECT_EQ("Lorem Ipsum", jbi::to_string("Lorem Ipsum"));
    EXPECT_EQ("1984", jbi::to_string(1984));
    EXPECT_EQ("3.14", jbi::to_string(3.14));
    EXPECT_EQ("z", jbi::to_string('z'));

}

TEST(to_sting_tests, types_with_to_string_method_test)
{
    using namespace ::testing;

    struct cxx_string_mock
    {
        MOCK_CONST_METHOD0(to_string, std::string());
    };

    cxx_string_mock cxx_mock;
    EXPECT_CALL(cxx_mock, to_string()).WillOnce(Return("Lorem Ipsum"));

    EXPECT_EQ("Lorem Ipsum", jbi::to_string(cxx_mock));

    struct c_string_mock
    {
        MOCK_CONST_METHOD0(to_string, const char*());
    };

    c_string_mock c_mock;
    EXPECT_CALL(c_mock, to_string()).WillOnce(Return("Lorem Ipsum"));

    EXPECT_EQ("Lorem Ipsum", jbi::to_string(c_mock));
}
