#include <gmock/gmock.h>

#include <jbi/core/variant.h>

using namespace ::testing;

TEST(core_variant_tests, default_constructor_test)
{
    jbi::variant<int, float> int_variant;
    EXPECT_EQ(0, jbi::get<int>(int_variant));

    jbi::variant<float, int> float_variant;
    EXPECT_EQ(0.0f, jbi::get<float>(float_variant));
}

TEST(core_variant_tests, destructor_test)
{
    class destructable_type
    {
    private:
        bool& _destructor_called;

    public:
        destructable_type(bool& destructor_called)
            : _destructor_called(destructor_called)
        { }

        ~destructable_type()
        {
            _destructor_called = true;
        }
    };

    bool destructor_called = false;

    {
        jbi::variant<int, destructable_type> variant{ destructable_type(destructor_called) };
    }

    EXPECT_TRUE(destructor_called);
};

TEST(core_variant_tests, apply_visitor_test)
{
    constexpr int expected_int = 1948;
    constexpr float expected_float = 3.14f;

    struct mock_visitor : public jbi::static_visitor<int>
    {
        MOCK_METHOD1(call_operator_int, int(int value));
        MOCK_METHOD1(call_operator_float, int(float value));

        int operator()(int value) { return call_operator_int(value); }
        int operator()(float value) { return call_operator_float(value); }
    };

    mock_visitor visitor;

    EXPECT_CALL(visitor, call_operator_int(expected_int)).Times(2).WillRepeatedly(Return(0));
    EXPECT_CALL(visitor, call_operator_float(expected_float)).Times(2).WillRepeatedly(Return(1));

    jbi::variant<int, float> int_variant(expected_int);
    EXPECT_EQ(0, int_variant.apply_visitor(visitor));

    jbi::variant<int, float> float_variant(expected_float);
    EXPECT_EQ(1, float_variant.apply_visitor(visitor));

    const jbi::variant<int, float> const_int_variant(expected_int);
    EXPECT_EQ(0, const_int_variant.apply_visitor(visitor));

    const jbi::variant<int, float> const_float_variant(expected_float);
    EXPECT_EQ(1, const_float_variant.apply_visitor(visitor));
}

TEST(core_variant_tests, get_test)
{
    jbi::variant<int, float> int_variant(1984);
    EXPECT_EQ(1984, jbi::get<int>(int_variant));
    EXPECT_THROW(jbi::get<float>(int_variant), jbi::bad_get);

    jbi::variant<int, float> float_variant(3.14f);
    EXPECT_EQ(3.14f, jbi::get<float>(float_variant));
    EXPECT_THROW(jbi::get<int>(float_variant), jbi::bad_get);

    const jbi::variant<int, float> const_int_variant(1948);
    EXPECT_EQ(1948, jbi::get<int>(const_int_variant));
    EXPECT_THROW(jbi::get<float>(const_int_variant), jbi::bad_get);

    const jbi::variant<int, float> const_float_variant(1.61f);
    EXPECT_EQ(1.61f, jbi::get<float>(const_float_variant));
    EXPECT_THROW(jbi::get<int>(const_float_variant), jbi::bad_get);
}
