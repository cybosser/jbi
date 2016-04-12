#include <gtest/gtest.h>

#include <jbi/core/variant.h>

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
