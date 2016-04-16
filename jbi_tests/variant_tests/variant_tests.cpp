#include <gmock/gmock.h>

#include <jbi/variant/variant.h>

using namespace ::testing;


template < typename T >
jbi::variant<int, float> make_variant(T value)
{
    return jbi::variant<int, float>(value);
};

TEST(core_variant_tests, default_constructor_test)
{
    jbi::variant<int, float> first;
    EXPECT_EQ(0, jbi::get<int>(first));
    EXPECT_THROW(jbi::get<float>(first), jbi::bad_get);

    jbi::variant<float, int> second;
    EXPECT_EQ(0.0f, jbi::get<float>(second));
    EXPECT_THROW(jbi::get<int>(second), jbi::bad_get);
}

TEST(core_variant_tests, copy_constructor_test)
{
    jbi::variant<int, float> variant(3.14f);

    jbi::variant<int, float> copy(variant);
    EXPECT_EQ(3.14f, jbi::get<float>(copy));
}

TEST(core_variant_tests, move_constructor_test)
{
    jbi::variant<int, float> int_variant(make_variant(1948));
    EXPECT_EQ(1948, jbi::get<int>(int_variant));

    jbi::variant<int, float> float_variant(make_variant(3.14f));
    EXPECT_EQ(3.14f, jbi::get<float>(float_variant));
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

TEST(core_variant_tests, copy_assignment_test)
{
    jbi::variant<int, float> variant(1948);

    jbi::variant<int, float> int_variant(1984);

    variant = int_variant;

    EXPECT_EQ(1984, jbi::get<int>(variant));
    EXPECT_EQ(1984, jbi::get<int>(int_variant));

    jbi::variant<int, float> float_variant(3.14f);

    variant = float_variant;

    EXPECT_EQ(3.14f, jbi::get<float>(variant));
    EXPECT_EQ(3.14f, jbi::get<float>(float_variant));
}

TEST(core_variant_tests, move_assignment_test)
{
    jbi::variant<int, float> variant(1948);

    variant = make_variant(1984);
    EXPECT_EQ(1984, jbi::get<int>(variant));

    variant = make_variant(3.14f);
    EXPECT_EQ(3.14f, jbi::get<float>(variant));
}

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

    EXPECT_CALL(visitor, call_operator_int(expected_int)).WillOnce(Return(0));
    EXPECT_CALL(visitor, call_operator_float(expected_float)).WillOnce(Return(1));

    jbi::variant<int, float> int_variant(expected_int);
    EXPECT_EQ(0, jbi::apply_visitor(int_variant, visitor));

    const jbi::variant<int, float> float_variant(expected_float);
    EXPECT_EQ(1, jbi::apply_visitor(float_variant, visitor));
}

TEST(core_variant_tests, get_test)
{
    jbi::variant<int, float> int_variant(1984);
    EXPECT_EQ(1984, jbi::get<int>(int_variant));
    EXPECT_THROW(jbi::get<float>(int_variant), jbi::bad_get);

    const jbi::variant<int, float> float_variant(3.14f);
    EXPECT_EQ(3.14f, jbi::get<float>(float_variant));
    EXPECT_THROW(jbi::get<int>(float_variant), jbi::bad_get);

    EXPECT_EQ(1948, jbi::get<int>(make_variant(1948)));
}

TEST(core_variant_tests, equality_operators_test)
{
    jbi::variant<int, float> first(1984);
    jbi::variant<int, float> second(1984);

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);

    jbi::variant<int, float> third(42);

    EXPECT_FALSE(first == third);
    EXPECT_TRUE(first != third);

    jbi::variant<int, float> fifth(42.0f);

    EXPECT_FALSE(first == fifth);
    EXPECT_TRUE(first != fifth);
}
