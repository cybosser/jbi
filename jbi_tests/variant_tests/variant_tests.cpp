#include <gmock/gmock.h>

#include <jbi/variant/variant.h>

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
    using namespace ::testing;

    struct destructable_mock
    {
        MOCK_METHOD0(destructor, void());

        ~destructable_mock()
        {
            destructor();
        }
    };

    destructable_mock* mock(new destructable_mock());

    EXPECT_CALL(*mock, destructor());

    {
        jbi::variant<int, std::unique_ptr<destructable_mock>> variant{ std::unique_ptr<destructable_mock>(mock) };
    }

    Mock::VerifyAndClearExpectations(mock);
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
    using namespace ::testing;

    constexpr int expected_int = 1948;
    constexpr float expected_float = 3.14f;

    struct mock_visitor : public jbi::static_visitor<int>
    {
        MOCK_CONST_METHOD1(call_operator_i, int(int));
        MOCK_CONST_METHOD1(call_operator_f, int(float));

        int operator()(int i) const { return call_operator_i(i); }
        int operator()(float f) const { return call_operator_f(f); }

        MOCK_CONST_METHOD2(call_operator_if, int(int, float));
        MOCK_CONST_METHOD2(call_operator_fi, int(float, int));
        MOCK_CONST_METHOD2(call_operator_ii, int(int, int));
        MOCK_CONST_METHOD2(call_operator_ff, int(float, float));

        int operator()(int i, float f) const { return call_operator_if(i, f); }
        int operator()(float f, int i) const { return call_operator_fi(f, i); }
        int operator()(int i1, int i2) const { return call_operator_ii(i1, i2); }
        int operator()(float f1, float f2) const { return call_operator_ff(f1, f2); }
    };

    mock_visitor visitor;

    EXPECT_CALL(visitor, call_operator_i(expected_int)).WillOnce(Return(0));
    EXPECT_CALL(visitor, call_operator_f(expected_float)).WillOnce(Return(1));

    EXPECT_CALL(visitor, call_operator_if(expected_int, expected_float)).WillOnce(Return(2));
    EXPECT_CALL(visitor, call_operator_fi(expected_float, expected_int)).WillOnce(Return(3));
    EXPECT_CALL(visitor, call_operator_ii(expected_int, expected_int)).WillOnce(Return(4));
    EXPECT_CALL(visitor, call_operator_ff(expected_float, expected_float)).WillOnce(Return(5));

    jbi::variant<int, float> int_variant(expected_int);
    jbi::variant<int, float> float_variant(expected_float);

    EXPECT_EQ(0, jbi::apply_visitor(visitor, int_variant));
    EXPECT_EQ(1, jbi::apply_visitor(visitor, float_variant));

    EXPECT_EQ(2, jbi::apply_visitor(visitor, int_variant, float_variant));
    EXPECT_EQ(3, jbi::apply_visitor(visitor, float_variant, int_variant));
    EXPECT_EQ(4, jbi::apply_visitor(visitor, int_variant, int_variant));
    EXPECT_EQ(5, jbi::apply_visitor(visitor, float_variant, float_variant));
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
