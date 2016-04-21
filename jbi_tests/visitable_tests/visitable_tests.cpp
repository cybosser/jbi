#include <gmock/gmock.h>

#include <jbi/visitor/accept_visitor.h>
#include <jbi/visitor/visitor.h>

struct base : public jbi::visitable
{ };

template < std::size_t >
struct derived : public base
{
    JBI_DEFINE_VISITABLE(derived)
};

TEST(visitable_tests, apply_visitor_test)
{
    using namespace ::testing;

    struct mock_visitor : jbi::visitor<int, derived<1>, derived<2>>
    {
        MOCK_CONST_METHOD1(call_operator_first, int(const derived<1>&));
        MOCK_CONST_METHOD1(call_operator_second, int(const derived<2>&));

        int operator()(const derived<1>& arg) { return call_operator_first(arg); }
        int operator()(const derived<2>& arg) { return call_operator_second(arg); }
    };

    mock_visitor visitor;

    EXPECT_CALL(visitor, call_operator_first(_)).WillOnce(Return(1));
    EXPECT_CALL(visitor, call_operator_second(_)).WillOnce(Return(2));

    derived<1> first;
    derived<2> second;

    EXPECT_EQ(1, jbi::accept_visitor(visitor, static_cast<base&>(first)));
    EXPECT_EQ(2, jbi::accept_visitor(visitor, static_cast<base&>(second)));

    derived<3> third;
    EXPECT_THROW(jbi::accept_visitor(visitor, static_cast<base&>(third)), jbi::argument_exception);
}
